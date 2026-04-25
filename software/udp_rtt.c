/*
 * udp_rtt.c — Medidor de RTT UDP con diagnóstico de drops del kernel
 *
 * Compilar:
 *   gcc -O3 -Wall -Wextra -o udp_rtt udp_rtt.c -lm
 *
 * Servidor:   ./udp_rtt -s [-p PUERTO]
 * Cliente:    ./udp_rtt -c 192.168.1.12 [-p 1234] [-i MS] [-z BYTES]
 *                       [-n COUNT] [-t TIMEOUT_MS] [-I eth0] [-o rtt.csv] [-q]
 *
 * INTERVALO (-i):  0 = FLOOD, 0.1 = 100 µs, 1 = 1 ms, etc.
 *
 * DIAGNÓSTICO DE DROPS (por qué aparecen timeouts sin corruptos):
 *   Un paquete con CRC malo es descartado ANTES de llegar a recv().
 *   El programa nunca lo ve → timeout. Hay 4 capas donde ocurre:
 *
 *   1. NIC hardware    → rx_crc_errors  (/sys/class/net/IFACE/statistics/)
 *                        FCS Ethernet malo; la NIC lo descarta antes del kernel
 *   2. Kernel UDP      → InCsumErrors   (/proc/net/snmp)
 *                        Checksum UDP malo; el kernel lo descarta
 *   3. Socket buffer   → RcvbufErrors   (/proc/net/snmp)
 *                        SO_RCVBUF lleno; el kernel descarta sin avisar
 *   4. Cola del socket → SO_RXQ_OVFL    (cmsg en cada recvmsg)
 *                        Overflow del ring buffer del socket
 *
 *   Con -I eth0 se monitorean los 4 niveles y se muestran los deltas al final.
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <signal.h>
#include <errno.h>
#include <getopt.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* ═══════════════════════════════════════════════════════════
 * Constantes
 * ═══════════════════════════════════════════════════════════ */
#define DEFAULT_PORT         1234
#define DEFAULT_PKT_SIZE     64
#define DEFAULT_INTERVAL_MS  1000.0
#define DEFAULT_TIMEOUT_MS   2000
#define MAX_PKT_SIZE         65507
#define HDR_MAGIC            0xC0FFEE42U
#define FAST_THRESHOLD_MS    50.0    /* por debajo → display agregado */

/* ═══════════════════════════════════════════════════════════
 * Cabecera del paquete — 24 bytes packed
 * ═══════════════════════════════════════════════════════════ */
typedef struct __attribute__((packed)) {
    uint32_t magic;
    uint32_t seq;
    uint64_t ts_ns;
    uint32_t pkt_size;
    uint32_t checksum;
} pkt_hdr_t;

#define HDR_SIZE  ((int)sizeof(pkt_hdr_t))

/* ═══════════════════════════════════════════════════════════
 * Estadísticas de RTT — Welford online
 * ═══════════════════════════════════════════════════════════ */
typedef struct {
    uint64_t sent;
    uint64_t recv;
    uint64_t timeout;
    uint64_t corrupt;
    uint64_t rxq_drops;    /* drops detectados via SO_RXQ_OVFL      */
    double   min_us;
    double   max_us;
    double   mean_us;
    double   M2_us;
    uint64_t t_start_ns;
    uint64_t t_end_ns;
} rtt_stats_t;

/* ═══════════════════════════════════════════════════════════
 * Estadísticas del kernel — leídas de /proc/net/snmp
 * Cada campo corresponde a una columna de la línea "Udp:"
 * ═══════════════════════════════════════════════════════════ */
typedef struct {
    uint64_t in_datagrams;
    uint64_t no_ports;
    uint64_t in_errors;       /* total errores de recepción           */
    uint64_t out_datagrams;
    uint64_t rcvbuf_errors;   /* drops por SO_RCVBUF lleno            */
    uint64_t sndbuf_errors;
    uint64_t in_csum_errors;  /* drops por checksum UDP malo          */
    uint64_t ignored_multi;
} proc_udp_t;

/* ═══════════════════════════════════════════════════════════
 * Estadísticas de la NIC — leídas de /sys/class/net/IFACE/statistics/
 * ═══════════════════════════════════════════════════════════ */
typedef struct {
    uint64_t rx_packets;
    uint64_t rx_errors;        /* errores RX totales del driver        */
    uint64_t rx_dropped;       /* drops del driver (no CRC)            */
    uint64_t rx_crc_errors;    /* FCS Ethernet malo → NIC descarta     */
    uint64_t rx_missed_errors; /* overflow FIFO de la NIC              */
    uint64_t rx_frame_errors;  /* errores de alineación de frame       */
} iface_stats_t;

static volatile sig_atomic_t g_running = 1;
static rtt_stats_t  g_rtt   = { .min_us = 1e18 };
static proc_udp_t   g_udp0, g_udp1;   /* snapshot antes / después     */
static iface_stats_t g_nic0, g_nic1;  /* snapshot antes / después     */
static char g_iface[64] = "";          /* nombre del interfaz (-I)     */

/* ═══════════════════════════════════════════════════════════
 * Utilidades de tiempo
 * ═══════════════════════════════════════════════════════════ */

static void on_signal(int s) { (void)s; g_running = 0; }

static inline uint64_t now_ns(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
}

static void sleep_until(uint64_t *next, uint64_t interval_ns)
{
    *next += interval_ns;
    struct timespec ts = {
        .tv_sec  = (time_t)(*next / 1000000000ULL),
        .tv_nsec = (long)  (*next % 1000000000ULL),
    };
    clock_nanosleep(CLOCK_MONOTONIC_RAW, TIMER_ABSTIME, &ts, NULL);
}

/* ═══════════════════════════════════════════════════════════
 * Lectura de /proc/net/snmp (estadísticas UDP del kernel)
 *
 * Formato del archivo:
 *   Udp: InDatagrams NoPorts InErrors OutDatagrams RcvbufErrors ...
 *   Udp: 12345       0       3        12345         1            ...
 * ═══════════════════════════════════════════════════════════ */
static int read_proc_udp(proc_udp_t *out)
{
    memset(out, 0, sizeof(*out));
    FILE *f = fopen("/proc/net/snmp", "r");
    if (!f) return -1;

    char line[512];
    /* Encontrar la segunda línea que empieza con "Udp:" (la de valores) */
    int found_header = 0;
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "Udp:", 4) != 0) continue;
        if (!found_header) { found_header = 1; continue; }
        /* Segunda línea: valores */
        sscanf(line, "Udp: %llu %llu %llu %llu %llu %llu %llu %llu",
               (unsigned long long *)&out->in_datagrams,
               (unsigned long long *)&out->no_ports,
               (unsigned long long *)&out->in_errors,
               (unsigned long long *)&out->out_datagrams,
               (unsigned long long *)&out->rcvbuf_errors,
               (unsigned long long *)&out->sndbuf_errors,
               (unsigned long long *)&out->in_csum_errors,
               (unsigned long long *)&out->ignored_multi);
        break;
    }
    fclose(f);
    return found_header ? 0 : -1;
}

/* ═══════════════════════════════════════════════════════════
 * Lectura de /sys/class/net/IFACE/statistics/CAMPO
 * ═══════════════════════════════════════════════════════════ */
static uint64_t read_sysfs_u64(const char *iface, const char *field)
{
    char path[256];
    snprintf(path, sizeof(path),
             "/sys/class/net/%s/statistics/%s", iface, field);
    FILE *f = fopen(path, "r");
    if (!f) return 0;
    uint64_t v = 0;
    fscanf(f, "%llu", (unsigned long long *)&v);
    fclose(f);
    return v;
}

static void read_iface_stats(const char *iface, iface_stats_t *out)
{
    memset(out, 0, sizeof(*out));
    if (!iface || !iface[0]) return;
    out->rx_packets      = read_sysfs_u64(iface, "rx_packets");
    out->rx_errors       = read_sysfs_u64(iface, "rx_errors");
    out->rx_dropped      = read_sysfs_u64(iface, "rx_dropped");
    out->rx_crc_errors   = read_sysfs_u64(iface, "rx_crc_errors");
    out->rx_missed_errors= read_sysfs_u64(iface, "rx_missed_errors");
    out->rx_frame_errors = read_sysfs_u64(iface, "rx_frame_errors");
}

/* ═══════════════════════════════════════════════════════════
 * Checksum del payload
 * ═══════════════════════════════════════════════════════════ */
static uint32_t calc_checksum(const uint8_t *buf, int size)
{
    uint32_t csum = 0;
    const uint8_t *p = buf + HDR_SIZE;
    int len = size - HDR_SIZE;
    for (int i = 0; i < len; i++)
        csum ^= ((uint32_t)p[i] << (8 * (i & 3)));
    return csum;
}

/* ═══════════════════════════════════════════════════════════
 * Welford online
 * ═══════════════════════════════════════════════════════════ */
static void welford_update(rtt_stats_t *s, double rtt_us)
{
    s->recv++;
    if (rtt_us < s->min_us) s->min_us = rtt_us;
    if (rtt_us > s->max_us) s->max_us = rtt_us;
    double d1    = rtt_us - s->mean_us;
    s->mean_us  += d1 / (double)s->recv;
    s->M2_us    += d1 * (rtt_us - s->mean_us);
}

/* ═══════════════════════════════════════════════════════════
 * Impresión de estadísticas + diagnóstico de drops
 * ═══════════════════════════════════════════════════════════ */
static void print_stats(const rtt_stats_t *s,
                        const proc_udp_t  *u0, const proc_udp_t  *u1,
                        const iface_stats_t *n0, const iface_stats_t *n1,
                        const char *iface)
{
    double stddev    = (s->recv > 1) ? sqrt(s->M2_us / (double)(s->recv - 1)) : 0.0;
    double loss_pct  = s->sent ? 100.0 * (double)(s->sent - s->recv) / (double)s->sent : 0.0;
    double elapsed_s = (s->t_end_ns > s->t_start_ns)
                     ? (double)(s->t_end_ns - s->t_start_ns) / 1e9 : 0.0;
    double pps_tx    = elapsed_s > 0 ? (double)s->sent / elapsed_s : 0.0;
    double pps_rx    = elapsed_s > 0 ? (double)s->recv / elapsed_s : 0.0;

    printf("\n");
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║             ESTADÍSTICAS DE RTT                  ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║  Tiempo total    : %-25.3f s  ║\n", elapsed_s);
    printf("║  Enviados        : %-28llu  ║\n", (unsigned long long)s->sent);
    printf("║  Recibidos       : %-28llu  ║\n", (unsigned long long)s->recv);
    printf("║  Timeouts        : %-28llu  ║\n", (unsigned long long)s->timeout);
    printf("║  Corruptos       : %-28llu  ║\n", (unsigned long long)s->corrupt);
    printf("║  Pérdida         : %-27.2f%%  ║\n", loss_pct);
    printf("║  PPS tx          : %-25.1f pps  ║\n", pps_tx);
    printf("║  PPS rx          : %-25.1f pps  ║\n", pps_rx);
    printf("╠══════════════════════════════════════════════════╣\n");
    if (s->recv > 0) {
        printf("║  RTT mínimo      : %-23.3f µs  ║\n", s->min_us);
        printf("║  RTT máximo      : %-23.3f µs  ║\n", s->max_us);
        printf("║  RTT media       : %-23.3f µs  ║\n", s->mean_us);
        printf("║  RTT stddev      : %-23.3f µs  ║\n", stddev);
    }
    printf("╚══════════════════════════════════════════════════╝\n");

    /*
     * ── DIAGNÓSTICO DE DROPS ──────────────────────────────────
     *
     * Mostramos los DELTAS (final - inicio) de cada contador del kernel.
     * Un valor > 0 indica que el kernel (o la NIC) descartó paquetes
     * en esa capa durante la prueba, causando timeouts en la aplicación.
     *
     * Interpretación:
     *   rx_crc_errors   > 0 → Hay errores FCS a nivel Ethernet.
     *                         La NIC los descarta antes del kernel.
     *                         Causa: cable malo, SFP deteriorado,
     *                                autoneg incorrecta, EMI.
     *
     *   rx_missed_errors> 0 → Overflow del FIFO de la NIC (DMA muy ocupado).
     *                         Causa: burst de tráfico, IRQ coalesce alto.
     *
     *   InCsumErrors    > 0 → Checksum UDP malo pasó el FCS Ethernet
     *                         pero el kernel lo descarta.
     *                         Causa: NIC con checksum offload roto,
     *                                bug de driver, corrupción en RAM.
     *
     *   RcvbufErrors    > 0 → El socket buffer (SO_RCVBUF) se llenó.
     *                         El kernel tiene el paquete pero no hay
     *                         espacio para encolarlo.
     *                         Causa: flooding demasiado rápido,
     *                                buffer muy pequeño.
     *
     *   RXQ drops       > 0 → Drop detectado por SO_RXQ_OVFL en este
     *                         socket específico (subconjunto de RcvbufErrors).
     * ────────────────────────────────────────────────────────── */
    printf("\n");
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║         DIAGNÓSTICO DE DROPS DEL KERNEL          ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");

    /* Nivel 4: socket (SO_RXQ_OVFL — este socket) */
    printf("║  [Socket] RXQ drops (SO_RXQ_OVFL)                ║\n");
    printf("║    drops este socket   : %-24llu  ║\n",
           (unsigned long long)s->rxq_drops);

    /* Nivel 3: UDP del kernel (/proc/net/snmp — todo el sistema) */
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║  [Kernel/UDP] /proc/net/snmp  (delta sistema)     ║\n");
    printf("║    InErrors            : %-24llu  ║\n",
           (unsigned long long)(u1->in_errors      - u0->in_errors));
    printf("║    InCsumErrors ← CRC  : %-24llu  ║\n",
           (unsigned long long)(u1->in_csum_errors - u0->in_csum_errors));
    printf("║    RcvbufErrors ← buf  : %-24llu  ║\n",
           (unsigned long long)(u1->rcvbuf_errors  - u0->rcvbuf_errors));

    /* Nivel 1 y 2: NIC (/sys/class/net/IFACE/statistics/) */
    printf("╠══════════════════════════════════════════════════╣\n");
    if (iface && iface[0]) {
        printf("║  [NIC] /sys/class/net/%-4s/statistics/           ║\n", iface);
        printf("║    rx_errors           : %-24llu  ║\n",
               (unsigned long long)(n1->rx_errors        - n0->rx_errors));
        printf("║    rx_crc_errors ← FCS : %-24llu  ║\n",
               (unsigned long long)(n1->rx_crc_errors    - n0->rx_crc_errors));
        printf("║    rx_missed_errors    : %-24llu  ║\n",
               (unsigned long long)(n1->rx_missed_errors - n0->rx_missed_errors));
        printf("║    rx_frame_errors     : %-24llu  ║\n",
               (unsigned long long)(n1->rx_frame_errors  - n0->rx_frame_errors));
        printf("║    rx_dropped          : %-24llu  ║\n",
               (unsigned long long)(n1->rx_dropped       - n0->rx_dropped));
    } else {
        printf("║  [NIC] No especificado (usa -I eth0 para ver)    ║\n");
        printf("║    Ejecuta también:                               ║\n");
        printf("║    ethtool -S eth0 | grep -iE 'crc|error|drop'   ║\n");
    }
    printf("╠══════════════════════════════════════════════════╣\n");

    /* Resumen interpretado */
    uint64_t crc_drop  = n1->rx_crc_errors    - n0->rx_crc_errors;
    uint64_t csum_drop = u1->in_csum_errors   - u0->in_csum_errors;
    uint64_t buf_drop  = u1->rcvbuf_errors    - u0->rcvbuf_errors;
    uint64_t nic_miss  = n1->rx_missed_errors - n0->rx_missed_errors;

    if (crc_drop == 0 && csum_drop == 0 && buf_drop == 0 &&
        nic_miss == 0 && s->rxq_drops == 0) {
        printf("║  CAUSA: No detectada por contadores del kernel.   ║\n");
        printf("║         Los timeouts son probablemente pérdidas   ║\n");
        printf("║         de red (congestión, switch, servidor).    ║\n");
    } else {
        printf("║  CAUSA PROBABLE DE LOS TIMEOUTS:                  ║\n");
        if (crc_drop > 0)
            printf("║  ✗ FCS Ethernet malo (NIC)  → %llu drops%.*s║\n",
                   (unsigned long long)crc_drop,
                   (int)(14 - (crc_drop > 9999 ? 5 : crc_drop > 999 ? 4 :
                               crc_drop > 99 ? 3 : crc_drop > 9 ? 2 : 1)), "          ");
        if (csum_drop > 0)
            printf("║  ✗ Checksum UDP malo       → %llu drops%.*s║\n",
                   (unsigned long long)csum_drop,
                   (int)(14 - (csum_drop > 9 ? 2 : 1)), "          ");
        if (buf_drop > 0)
            printf("║  ✗ SO_RCVBUF lleno         → %llu drops%.*s║\n",
                   (unsigned long long)buf_drop,
                   (int)(14 - (buf_drop > 9 ? 2 : 1)), "          ");
        if (nic_miss > 0)
            printf("║  ✗ FIFO overflow NIC       → %llu drops%.*s║\n",
                   (unsigned long long)nic_miss,
                   (int)(14 - (nic_miss > 9 ? 2 : 1)), "          ");
    }
    printf("╚══════════════════════════════════════════════════╝\n");

    if (iface && iface[0])
        printf("\nNota: los contadores de NIC son del sistema completo,\n"
               "no solo de tus paquetes. Para aislar al 100%% usa:\n"
               "  ethtool -S %s | grep -iE 'crc|error|miss|drop'\n", iface);
}

/* ═══════════════════════════════════════════════════════════
 * Servidor
 * ═══════════════════════════════════════════════════════════ */
static int run_server(int port)
{
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd < 0) { perror("socket"); return 1; }

    int one = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &one, sizeof(one));
    int buf = 8 * 1024 * 1024;
    setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &buf, sizeof(buf));
    setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &buf, sizeof(buf));

    struct sockaddr_in addr = {
        .sin_family      = AF_INET,
        .sin_port        = htons((uint16_t)port),
        .sin_addr.s_addr = INADDR_ANY,
    };
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind"); close(fd); return 1;
    }

    printf("[SERVIDOR] UDP:%d  (Ctrl+C para salir)\n\n", port);
    signal(SIGINT, on_signal); signal(SIGTERM, on_signal);

    static uint8_t pkt[MAX_PKT_SIZE];
    struct sockaddr_in peer;
    socklen_t plen;
    uint64_t echoed = 0, t_last = now_ns();

    while (g_running) {
        plen = sizeof(peer);
        ssize_t n = recvfrom(fd, pkt, sizeof(pkt), 0,
                             (struct sockaddr *)&peer, &plen);
        if (n < 0) { if (errno == EINTR) break; perror("recvfrom"); continue; }
        sendto(fd, pkt, (size_t)n, MSG_DONTWAIT,
               (struct sockaddr *)&peer, plen);
        echoed++;
        uint64_t now = now_ns();
        if (now - t_last >= 1000000000ULL) {
            printf("[SERVIDOR] Ecos: %llu\r", (unsigned long long)echoed);
            fflush(stdout);
            t_last = now;
        }
    }
    printf("\n[SERVIDOR] %llu ecos.\n", (unsigned long long)echoed);
    close(fd);
    return 0;
}

/* ═══════════════════════════════════════════════════════════
 * Cliente
 * ═══════════════════════════════════════════════════════════ */
static int run_client(const char *host, int port,
                      int pkt_size, double interval_ms,
                      long count, int timeout_ms,
                      const char *csv_path, int quiet)
{
    if (pkt_size < HDR_SIZE) {
        fprintf(stderr, "Tamaño mínimo: %d bytes\n", HDR_SIZE); return 1;
    }
    if (pkt_size > MAX_PKT_SIZE) {
        fprintf(stderr, "Tamaño máximo: %d bytes\n", MAX_PKT_SIZE); return 1;
    }

    int flood_mode   = (interval_ms == 0.0);
    int fast_display = quiet || flood_mode || (interval_ms < FAST_THRESHOLD_MS);

    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd < 0) { perror("socket"); return 1; }

    int buf = 8 * 1024 * 1024;
    setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &buf, sizeof(buf));
    setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &buf, sizeof(buf));

    int tos = 0xB8;   /* DSCP EF — cola de baja latencia */
    setsockopt(fd, IPPROTO_IP, IP_TOS, &tos, sizeof(tos));

    /*
     * SO_RXQ_OVFL: añade un cmsg a cada recvmsg() con el número de
     * paquetes que el kernel descartó en la cola de este socket
     * desde el último recv exitoso. Requiere Linux 2.6.33+.
     */
    int one = 1;
    setsockopt(fd, SOL_SOCKET, SO_RXQ_OVFL, &one, sizeof(one));

    struct sockaddr_in dest = {
        .sin_family = AF_INET,
        .sin_port   = htons((uint16_t)port),
    };
    if (inet_pton(AF_INET, host, &dest.sin_addr) != 1) {
        fprintf(stderr, "IP inválida: %s\n", host); close(fd); return 1;
    }
    if (connect(fd, (struct sockaddr *)&dest, sizeof(dest)) < 0) {
        perror("connect"); close(fd); return 1;
    }

    struct timeval tv = {
        .tv_sec  = timeout_ms / 1000,
        .tv_usec = (timeout_ms % 1000) * 1000,
    };
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    uint8_t *snd = malloc((size_t)pkt_size);
    uint8_t *rcv = malloc((size_t)pkt_size);
    if (!snd || !rcv) { perror("malloc"); close(fd); return 1; }
    memset(snd + HDR_SIZE, 0xAB, (size_t)(pkt_size - HDR_SIZE));
    uint32_t pcsum = calc_checksum(snd, pkt_size);

    /* Buffer de control para recvmsg (cmsg de SO_RXQ_OVFL) */
    char ctrl[CMSG_SPACE(sizeof(uint32_t))];

    FILE *csv = NULL;
    if (csv_path) {
        csv = fopen(csv_path, "w");
        if (!csv) perror("fopen csv");
        else      fprintf(csv, "seq,rtt_us,status,rxq_drops_delta\n");
    }

    signal(SIGINT, on_signal); signal(SIGTERM, on_signal);

    /* Snapshot inicial de contadores del kernel */
    read_proc_udp(&g_udp0);
    read_iface_stats(g_iface, &g_nic0);

    printf("UDP RTT  →  %s:%d\n", host, port);
    printf("Modo: %s  |  tamaño=%d B  |  timeout=%d ms\n\n",
           flood_mode ? "FLOOD" : "intervalo",
           pkt_size, timeout_ms);

    if (!fast_display) {
        printf("%-10s  %14s  %10s  %s\n",
               "Seq", "RTT (µs)", "RXQ drops", "Estado");
        printf("──────────────────────────────────────────────────\n");
    } else if (!quiet) {
        printf("[Modo rápido: display 1 vez/segundo]\n\n");
        printf("  %-10s %-10s %-14s %-14s %-14s %-10s %-10s\n",
               "Enviados", "Recibidos", "RTT med(µs)",
               "RTT min(µs)", "RTT max(µs)", "PPS", "RXQ drops");
        printf("  ──────────────────────────────────────────────────────────────────────────────────\n");
    }

    uint64_t interval_ns    = flood_mode ? 0ULL : (uint64_t)(interval_ms * 1e6);
    uint64_t next_wake      = now_ns();
    uint64_t t_last_display = next_wake;
    g_rtt.t_start_ns        = next_wake;
    uint32_t seq = 0;

    while (g_running && (count == 0 || (long)seq < count)) {

        /* Construir paquete */
        pkt_hdr_t hdr = {
            .magic    = HDR_MAGIC,
            .seq      = seq,
            .ts_ns    = 0,
            .pkt_size = (uint32_t)pkt_size,
            .checksum = pcsum,
        };
        memcpy(snd, &hdr, HDR_SIZE);

        uint64_t t_send = now_ns();
        ((pkt_hdr_t *)snd)->ts_ns = t_send;

        ssize_t nsent = send(fd, snd, (size_t)pkt_size, 0);
        g_rtt.sent++;

        if (nsent < 0) {
            if (!fast_display)
                printf("%-10u  %14s  %10s  ERROR SEND\n", seq, "-", "-");
            if (csv) fprintf(csv, "%u,,error_send,0\n", seq);
            goto next_pkt;
        }

        /*
         * recvmsg() en lugar de recv() para leer el cmsg SO_RXQ_OVFL.
         * El cmsg nos dice cuántos paquetes descartó el kernel en la
         * cola de ESTE socket desde el último recv exitoso.
         */
        {
            struct iovec iov = { .iov_base = rcv, .iov_len = (size_t)pkt_size };
            struct msghdr msg = {
                .msg_iov        = &iov,
                .msg_iovlen     = 1,
                .msg_control    = ctrl,
                .msg_controllen = sizeof(ctrl),
                .msg_name       = NULL,
                .msg_namelen    = 0,
            };

            ssize_t nrcv = recvmsg(fd, &msg, 0);
            uint64_t t_recv = now_ns();

            /* Leer drops del cmsg SO_RXQ_OVFL */
            uint32_t rxq_delta = 0;
            for (struct cmsghdr *cm = CMSG_FIRSTHDR(&msg);
                 cm != NULL;
                 cm = CMSG_NXTHDR(&msg, cm))
            {
                if (cm->cmsg_level == SOL_SOCKET &&
                    cm->cmsg_type  == SO_RXQ_OVFL)
                {
                    memcpy(&rxq_delta, CMSG_DATA(cm), sizeof(rxq_delta));
                    g_rtt.rxq_drops += rxq_delta;
                    break;
                }
            }

            if (nrcv < 0) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    g_rtt.timeout++;
                    if (!fast_display)
                        printf("%-10u  %14s  %10u  TIMEOUT\n",
                               seq, "-", rxq_delta);
                    if (csv) fprintf(csv, "%u,,timeout,%u\n", seq, rxq_delta);
                } else {
                    if (!fast_display)
                        printf("%-10u  %14s  %10u  ERROR RECV\n",
                               seq, "-", rxq_delta);
                    if (csv) fprintf(csv, "%u,,error_recv,%u\n", seq, rxq_delta);
                }
                goto next_pkt;
            }

            if (nrcv != (ssize_t)pkt_size ||
                memcmp(snd, rcv, (size_t)pkt_size) != 0)
            {
                g_rtt.corrupt++;
                if (!fast_display)
                    printf("%-10u  %14s  %10u  CORRUPTO\n",
                           seq, "-", rxq_delta);
                if (csv) fprintf(csv, "%u,,corrupt,%u\n", seq, rxq_delta);
                goto next_pkt;
            }

            double rtt_us = (double)(t_recv - t_send) / 1000.0;
            welford_update(&g_rtt, rtt_us);
            if (!fast_display)
                printf("%-10u  %14.3f  %10u  OK\n", seq, rtt_us, rxq_delta);
            if (csv) fprintf(csv, "%u,%.3f,ok,%u\n", seq, rtt_us, rxq_delta);
        }

    next_pkt:
        seq++;

        if (fast_display && !quiet) {
            uint64_t now = now_ns();
            if (now - t_last_display >= 1000000000ULL) {
                double elapsed = (double)(now - g_rtt.t_start_ns) / 1e9;
                double pps = elapsed > 0 ? (double)g_rtt.recv / elapsed : 0.0;
                printf("  %-10llu %-10llu %-14.3f %-14.3f %-14.3f %-10.1f %-10llu\n",
                       (unsigned long long)g_rtt.sent,
                       (unsigned long long)g_rtt.recv,
                       g_rtt.mean_us,
                       g_rtt.min_us < 1e17 ? g_rtt.min_us : 0.0,
                       g_rtt.max_us,
                       pps,
                       (unsigned long long)g_rtt.rxq_drops);
                fflush(stdout);
                t_last_display = now;
            }
        }

        if (!flood_mode && g_running && (count == 0 || (long)seq < count))
            sleep_until(&next_wake, interval_ns);
        else if (!flood_mode)
            next_wake += interval_ns;
    }

    g_rtt.t_end_ns = now_ns();

    /* Snapshot final de contadores del kernel */
    read_proc_udp(&g_udp1);
    read_iface_stats(g_iface, &g_nic1);

    free(snd); free(rcv);
    close(fd);
    if (csv) { fflush(csv); fclose(csv); }

    print_stats(&g_rtt, &g_udp0, &g_udp1, &g_nic0, &g_nic1, g_iface);
    return 0;
}

/* ═══════════════════════════════════════════════════════════
 * main
 * ═══════════════════════════════════════════════════════════ */
static void usage(const char *prog)
{
    fprintf(stderr,
        "Uso:\n"
        "  Servidor : %s -s [-p PUERTO]\n"
        "  Cliente  : %s -c HOST [opciones]\n"
        "\n"
        "Opciones:\n"
        "  -s           Modo servidor (echo)\n"
        "  -c HOST      IP destino\n"
        "  -p PUERTO    Puerto UDP                (default: %d)\n"
        "  -z BYTES     Tamaño del paquete        (default: %d, mín: %d)\n"
        "  -i MS        Intervalo en ms           (0=FLOOD, 0.1=100µs)\n"
        "  -n COUNT     Núm. paquetes             (0=infinito)\n"
        "  -t TIMEOUT   Timeout recv ms           (default: %d)\n"
        "  -I IFACE     Interfaz para stats NIC   (ej: eth0, ens3)\n"
        "  -o FILE.csv  Guardar RTT en CSV\n"
        "  -q           Silencioso (sólo stats finales)\n"
        "\n"
        "Diagnóstico de drops:\n"
        "  Sin -I: muestra solo drops UDP del kernel (/proc/net/snmp)\n"
        "  Con -I: muestra además drops de la NIC (/sys/class/net/)\n"
        "\n"
        "Ejemplos:\n"
        "  %s -s\n"
        "  %s -c 192.168.1.12 -i 1 -I eth0 -n 1000\n"
        "  %s -c 192.168.1.12 -i 0 -I eth0 -q -o flood.csv\n",
        prog, prog,
        DEFAULT_PORT, DEFAULT_PKT_SIZE, HDR_SIZE, DEFAULT_TIMEOUT_MS,
        prog, prog, prog);
}

int main(int argc, char *argv[])
{
    int    mode        = 0;
    int    port        = DEFAULT_PORT;
    int    pkt_size    = DEFAULT_PKT_SIZE;
    double interval_ms = DEFAULT_INTERVAL_MS;
    long   count       = 0;
    int    timeout_ms  = DEFAULT_TIMEOUT_MS;
    int    quiet       = 0;
    char   host[64]    = "";
    char   csv_path[256] = "";

    int opt;
    while ((opt = getopt(argc, argv, "sc:p:z:i:n:t:I:o:qh")) != -1) {
        switch (opt) {
        case 's': mode = 's'; break;
        case 'c': mode = 'c'; snprintf(host,     sizeof(host),     "%s", optarg); break;
        case 'I':             snprintf(g_iface,   sizeof(g_iface),  "%s", optarg); break;
        case 'o':             snprintf(csv_path,  sizeof(csv_path), "%s", optarg); break;
        case 'p': port        = atoi(optarg); break;
        case 'z': pkt_size    = atoi(optarg); break;
        case 'i': interval_ms = atof(optarg); break;
        case 'n': count       = atol(optarg); break;
        case 't': timeout_ms  = atoi(optarg); break;
        case 'q': quiet = 1; break;
        case 'h': usage(argv[0]); return 0;
        default:  usage(argv[0]); return 1;
        }
    }

    if (mode == 0) { usage(argv[0]); return 1; }
    if (mode == 'c' && !host[0]) { fprintf(stderr, "Falta -c HOST\n"); return 1; }
    if (port < 1 || port > 65535) { fprintf(stderr, "Puerto inválido\n"); return 1; }
    if (interval_ms < 0.0) { fprintf(stderr, "Intervalo inválido\n"); return 1; }
    if (timeout_ms < 1) { fprintf(stderr, "Timeout mínimo 1 ms\n"); return 1; }

    if (mode == 's') return run_server(port);
    return run_client(host, port, pkt_size, interval_ms, count,
                      timeout_ms, csv_path[0] ? csv_path : NULL, quiet);
}
