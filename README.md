# Spartan-6 1GbE Interface

![Board photo](https://github.com/user-attachments/assets/d1b2b5ab-4048-4e31-9e69-e21ac2fdd364)

A **1 Gbps Ethernet UDP communication system** implemented on a Xilinx Spartan-6 FPGA with a KSZ9031 Gigabit PHY. Achieves ~1 Gbps throughput in TX, RX, and full-duplex modes, controlled via UART or UDP commands.

## Hardware

| Component | Part |
|-----------|------|
| FPGA | Xilinx Spartan-6 XC6SLX9-2TQG144C |
| PHY | KSZ9031RNXCC |
| Connector | ARJM11B1-502-AB-EW2 |

---

## Features

- **UDP TX/RX** at line rate (~1 Gbps)
- **Full-duplex** simultaneous TX + RX (237 MB/s measured)
- **UART control interface** — configure and trigger tests via serial commands
- **UDP command interface** — remotely set packet count, size, and rate
- **ARP support** — FPGA responds to ARP requests
- **Software shutdown mode** — low-power state via command (~159 mA)

---

## Board Controls

### Switches & LEDs

| Switch | Function | LED | Indicates |
|--------|----------|-----|-----------|
| SW[0] | Indicator state | LED[0] | Global reset_n |
| SW[1] | Indicator state | LED[1] | UART/MDIO reset_n |
| SW[2] | Indicator state | LED[2] | PHY PLL 125 MHz_n |
| SW[3] | Indicator state | LED[3] | PHY interrupt |
| SW[4] | Indicator state | LED[4] | UDP loopback mode |
| SW[5] | Indicator state | LED[5] | UDP random or constant data mode |
| SW[6] | Indicator state | LED[6] | UDP transmitting |
| SW[7] | Indicator state | LED[7] | MDIO busy |

### Push Buttons

| Button | Function |
|--------|----------|
| PUSH[0] | PHY reset |
| PUSH[1] | Reset UART and MDIO interfaces |
| PUSH[2] | Global reset |

---

## UDP Operation Modes

| Mode | Description |
|------|-------------|
| Default | Generate and transmit sequence data |
| Loopback | Echo received packets back to sender |
| Random data | Generate and transmit random data |
| Constant data | Transmit predefined data "X" or h58 |

---

## UART Command Interface

### Serial Configuration

| Parameter | Value |
|-----------|-------|
| Baud rate | 115200 |
| Data bits | 8 |
| Stop bits | 1 |
| Parity | None |

### Sending Commands

Commands are sent using `send_uart.py`. Multiple commands can be chained in a single call — they are concatenated in order with no separator:

```bash
python3 send_uart.py command1 command2 command3
```

> **Hardware constraint:** every transmission must be exactly **8 bytes or a multiple of 8 bytes**. The script enforces this and will error before touching the serial port if the length is wrong.

---

### UDP Control Commands
| Command | Hex | Description |
|---------|-----|-------------|
| `loopback` | `6C6F6F706261636B` | Enable loopback mode (LED[4] on) |
| `.trigger` | `2E74726967676572` | Send a trigger pulse |
| `..random` | `2E2E72616E646F6D` | Enable random data mode (LED[5] on) |
| `...flood` | `2E2E2E666C6F6F64` | Transmit as fast as possible |
| `udpmtu\xHH\xHH` | `7564706D7475HHHH` | Set MTU size (16-bit, default `\x05\xA0` = 1440 B) |
| `pktn\xHH\xHH\x00\x00` | `706B746EHHHHHHHH` | Set packet count per trigger (32-bit, default `\x00\x00\x00\x01` = 1) |

---

### IP / Network Configuration Commands
| Command | Hex | Description |
|---------|-----|-------------|
| `ip_g\xII\xII\xII\xII` | `69705F67IIIIIIII` | Set gateway IP (32-bit) |
| `ip_s\xII\xII\xII\xII` | `69705F73IIIIIIII` | Set local/source IP (32-bit) |
| `ip_d\xII\xII\xII\xII` | `69705F64IIIIIIII` | Set destination IP (32-bit) |
| `subm\xMM\xMM\xMM\xMM` | `7375626DMMMMMMM` | Set subnet mask (32-bit) |
| `srport\xPP\xPP` | `7372706F7274PPPP` | Set UDP source port (16-bit) |
| `dsport\xPP\xPP` | `6473706F7274PPPP` | Set UDP destination port (16-bit) |

> **IP format:** IPs are sent as raw 32-bit big-endian values.
> Example: `192.168.1.100` → `\xC0\xA8\x01\x64`

---

### MDIO / PHY Control Commands
| Command | Hex | Description |
|---------|-----|-------------|
| `..mdio_w` | `2E2E6D64696F5F77` | Switch to MDIO write mode |
| `..mdio_r` | `2E2E6D64696F5F72` | Switch to MDIO read mode (default) |
| `phyaddr\xHH` | `70687961646472HH` | Set PHY address (5 LSBs of `\xHH`, default `\x07`) |
| `regaddr\xHH` | `72656761646472HH` | Set register address (5 LSBs of `\xHH`, default `\x00`) |
| `mdio_d\xHH\xHH` | `6D64696F5F64HHHH` | Set 16-bit write data |
| `mdio_sta` | `6D64696F5F737461` | Start MDIO operation |

### MDIO Transaction Sequence

```
1. Set mode      →  ..mdio_r  or  ..mdio_w
2. Set PHY addr  →  phyaddr\xHH
3. Set reg addr  →  regaddr\xHH
4. Set data      →  mdio_d\xHH\xHH   (write operations only)
5. Execute       →  mdio_sta
```

Always return to read mode after a write to leave the interface in a safe state.

---

## Command Examples

### Read PHY register (default config)

```bash
python3 send_uart.py ..mdio_r "phyaddr\x07" "regaddr\x00" mdio_sta
```

Sequence: read mode → PHY 7 → register 0 → execute

---

### Write to PHY register, then read back to confirm

```bash
python3 send_uart.py ..mdio_w "phyaddr\x07" "regaddr\x00" "mdio_d\x11\x40" mdio_sta ..mdio_r mdio_sta
```

| Step | Command | Action |
|------|---------|--------|
| 1 | `..mdio_w` | Switch to write mode |
| 2 | `phyaddr\x07` | Target PHY 7 |
| 3 | `regaddr\x00` | Target register 0 |
| 4 | `mdio_d\x11\x40` | Write data = 0x1140 |
| 5 | `mdio_sta` | Execute write |
| 6 | `..mdio_r` | Switch back to read mode |
| 7 | `mdio_sta` | Execute read (verify) |

---

### Common MDIO sequences

| Purpose | Command |
|---------|---------|
| Read PHY 7, reg 0 | `python3 send_uart.py ..mdio_r "phyaddr\x07" "regaddr\x00" mdio_sta` |
| Write default config (PHY 7, reg 0) | `python3 send_uart.py ..mdio_w "phyaddr\x07" "regaddr\x00" "mdio_d\x11\x40" mdio_sta ..mdio_r mdio_sta` |
| Software reset (PHY 7) | `python3 send_uart.py ..mdio_w "phyaddr\x07" "regaddr\x00" "mdio_d\x91\x40" mdio_sta ..mdio_r mdio_sta` |
| Power down (PHY 7) | `python3 send_uart.py ..mdio_w "phyaddr\x07" "regaddr\x00" "mdio_d\x19\x40" mdio_sta ..mdio_r mdio_sta` |

---

### MDIO MMD Register Access

MMD (MIIM Managed Device) registers are accessed indirectly using the **MDIO address registers D (0x0D) and E (0x0E)**.

The access sequence is always:
1. Write the MMD device address to register `0x0D`
2. Write the target register address to register `0x0E`
3. Write the function (read/write + optional auto-increment) back to `0x0D`
4. Read or write data via register `0x0E`

#### Write MMD — Example: MMD device `0x02`, register `0x00` ← `0x0010`

```bash
# Step 1 — Select MMD device address (device = 0x02)
python3 send_uart.py ..mdio_w "phyaddr\x07" "regaddr\x0D" "mdio_d\x00\x02" mdio_sta

# Step 2 — Select target register inside the MMD (register = 0x0000)
python3 send_uart.py ..mdio_w "phyaddr\x07" "regaddr\x0E" "mdio_d\x00\x00" mdio_sta

# Step 3 — Switch to data function, no auto-increment (0x4000 | device)
python3 send_uart.py ..mdio_w "phyaddr\x07" "regaddr\x0D" "mdio_d\x40\x02" mdio_sta

# Step 4 — Write new data to the MMD register
python3 send_uart.py ..mdio_w "phyaddr\x07" "regaddr\x0E" "mdio_d\x00\x10" mdio_sta
```

> **`0x4002`** = data function (bits [15:14] = `01`) + device `0x02`, no auto-increment.
> **`0x8002`** = data function with post-increment (bits [15:14] = `10`) + device `0x02`.

---

#### Read MMD — Example: MMD device `0x02`, registers `0x00` → `0x02` (burst with auto-increment)

```bash
# Step 1 — Select MMD device address (device = 0x02)
python3 send_uart.py ..mdio_w "phyaddr\x07" "regaddr\x0D" "mdio_d\x00\x02" mdio_sta

# Step 2 — Select starting register (register = 0x0000)
python3 send_uart.py ..mdio_w "phyaddr\x07" "regaddr\x0E" "mdio_d\x00\x00" mdio_sta

# Step 3 — Switch to data function WITH auto-increment (0x8000 | device)
python3 send_uart.py ..mdio_w "phyaddr\x07" "regaddr\x0D" "mdio_d\x80\x02" mdio_sta

# Step 4 — Read register 0x00
python3 send_uart.py ..mdio_r "phyaddr\x07" "regaddr\x0E" mdio_sta

# Step 5 — Read register 0x01 (auto-incremented)
python3 send_uart.py ..mdio_r "phyaddr\x07" "regaddr\x0E" mdio_sta

# Step 6 — Read register 0x02 (auto-incremented)
python3 send_uart.py ..mdio_r "phyaddr\x07" "regaddr\x0E" mdio_sta
```

---

#### One-liner shortcuts

```bash
# Full write — MMD 0x02, reg 0x00 ← 0x0008
python3 send_uart.py ..mdio_w \
  "phyaddr\x07" "regaddr\x0D" "mdio_d\x00\x02" mdio_sta \
  "regaddr\x0E" "mdio_d\x00\x00"               mdio_sta \
  "regaddr\x0D" "mdio_d\x40\x02"               mdio_sta \
  "regaddr\x0E" "mdio_d\x00\x08"               mdio_sta

# Full read — MMD 0x02, reg 0x00 (single, no auto-increment)
python3 send_uart.py ..mdio_w \
  "phyaddr\x07" "regaddr\x0D" "mdio_d\x00\x02" mdio_sta \
  "regaddr\x0E" "mdio_d\x00\x00"               mdio_sta \
  "regaddr\x0D" "mdio_d\x40\x02"               mdio_sta \
  ..mdio_r "regaddr\x0E" mdio_sta
```

#### Register `0x0D` function field reference

| Bits [15:14] | Value | Function |
|---|---|---|
| `00` | `0x0000` \| device | Address function — points to MMD register |
| `01` | `0x4000` \| device | Data function — no auto-increment |
| `10` | `0x8000` \| device | Data function — post-increment on each access read or write |
| `11` | `0xC000` \| device | Data function — post increment on writes only |

---

## Network Setup

Set up a `192.168.1.1/24` network between your PC and the FPGA:

| Device | IP Address |
|--------|------------|
| FPGA (default) | `192.168.1.12` |
| PC (default) | `192.168.1.11` |

> IPv6 must be disabled on the interface for compatibility.

Configure the PC interface:

```bash
sudo ip addr flush dev eth0
sudo ip addr add 192.168.1.11/24 dev eth0
sudo ip link set eth0 up
```

Verify ARP (confirms the FPGA link is up):

```bash
sudo arping -I eth0 -c 10 192.168.1.12
```

---

## Throughput Tests

### TX Test (~1 Gbps)

Terminal 1 — monitor traffic:
```bash
sudo tcpdump -i eth0 udp -w - | pv > /dev/null
```

Terminal 2 — trigger transmission (set ~1 M packets first for accurate results):
```bash
python3 send_uart.py .trigger
```

> Expected: **~118 MB/s ≈ 0.994 Gbps**

---

### RX Test

Terminal 1 — flood UDP packets to the FPGA:
```bash
sudo hping3 192.168.1.12 -2 -p 1234 -d 1440 --flood
```

Terminal 2 — monitor received traffic:
```bash
sudo tcpdump -i eth0 udp -w - | pv > /dev/null
```

---

### Full-Duplex Test (TX + RX simultaneously)

Run both the TX and RX tests at the same time and monitor with:
```bash
sudo tcpdump -i eth0 udp -w - | pv > /dev/null
```

> **Measured: 237 MB/s (~1 Gbps full-duplex confirmed)**
> ```
> tcpdump: listening on eth0, link-type EN10MB (Ethernet), snapshot length 262144 bytes
> 26.9GiB 0:03:54 [236MiB/s]
> ```

---

## Power Consumption

Measurements include FPGA + PHY at 1 Gbps link speed.

| Mode | Current |
|------|---------|
| Standby (1 Gbps link up) | ~467 mA |
| Software shutdown | ~159 mA |
| Full duplex (1 Gbps) | ~552 mA |

---

## Troubleshooting

| Symptom | Solution |
|---------|---------|
| No response from FPGA | Check USB connection and power supply |
| LEDs all off | Verify switch positions (SW[1] enables LEDs) |
| LED[7] stuck on | MDIO busy — wait for operation to complete before sending next command |
| Unexpected data received | Verify baud rate is set to 115200 |
| Script errors before sending | Payload length must be a multiple of 8 bytes — add `\x00` padding |
