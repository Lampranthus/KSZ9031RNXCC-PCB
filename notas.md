# Documento Técnico: Procedimiento Estándar de Pruebas Ethernet Gigabit (FPGA)

## 1. Verificación de Hardware (Diagnóstico Visual)
Al encender la FPGA, el estado inicial del sistema debe verificarse a través de los indicadores LED integrados en la placa.

### 1.1 Estado de LEDs de Sistema (FPGA)
| LED | Función | Estado Normal / Esperado | Significado en caso de error |
| :--- | :--- | :--- | :--- |
| **LED 1** | Global `rst_n` | **Encendido** | Si está apagado, el sistema está en reset global. |
| **LED 2** | Reset UART / MDIO | **Encendido** | Si está apagado, bloqueos UART/MDIO inactivos. |
| **LED 3** | PHY PLL Status | **Encendido (Tenue)** | Si brilla con alta intensidad, el reloj del PHY falló (Requiere reinicio físico). *Nota: Tras configurar MDIO, brilla normal.* |
| **LED 4** | Interrupción PHY | **Apagado** | Reservado/Configurable por registros PHY. |
| **LED 5** | Modo Loopback | **Apagado** | Si está encendido, FPGA ignora triggers y rebota tráfico. |
| **LED 6** | Modo Payload | **Apagado** | Encendido indica modo de datos Aleatorios o Constantes. |
| **LED 7** | Actividad TX | **Apagado / Parpadeo** | Se enciende/parpadea durante la transmisión de datos. |
| **LED 8** | Actividad MDIO | **Parpadeo** | Muestra actividad al enviar comandos de configuración PHY. |

### 1.2 Estado de LEDs del Puerto RJ45
* **Modo Por Defecto (Single Mode):**
    * 🟢 **Verde:** Enlace físico establecido.
    * 🟠 **Naranja:** Actividad de red detectada (No indica velocidad).
* **Modo Configurado (Dual Mode - Post MDIO Setup):**
    * 🟢 **Verde (Sólido):** Enlace negociado exitosamente a **1 GbE**.
    * 🟢 **Verde (Parpadeo rápido):** Transmisión/Recepción a 1 GbE activa.
    * *Cualquier otro comportamiento indica que no se alcanzó velocidad Gigabit.*

---

## 2. Configuración del Enlace y Hardware (Setup)

La comunicación de control se realiza mediante la interfaz FT232 (USB-UART) utilizando el script `send_uart.py`.

### 2.1 Configuración de Red Base
El sistema requiere que el PC host y la FPGA estén en la misma subred.
* **PC Host (Por defecto):** `192.168.1.11`
* **FPGA (Por defecto):** `192.168.1.12`

Comandos UART para reconfiguración (8 bytes por comando):
```bash
# Cambiar Gateway (Por defecto: 192.168.1.1)
python3 send_uart.py "ip_g\xCO\xA8\x01\x01" 

# Cambiar Submáscara (Por defecto: 255.255.255.0)
python3 send_uart.py "subm\xFF\xFF\xFF\x00"

# Cambiar IP de la FPGA (Por defecto: 192.168.1.12)
python3 send_uart.py "ip_s\xCO\xA8\x01\x0C"

# Cambiar IP de Destino (PC Host) (Por defecto: 192.168.1.11)
python3 send_uart.py "ip_d\xCO\xA8\x01\x0B"
```

### 2.2 Configuración de Registros PHY (Vía MDIO)
Para garantizar estabilidad a 1 GbE, se debe eliminar el PLL hacia la FPGA, habilitar el "Dual Mode" del LED RJ45 y ajustar los delays RGMII. Se envía la siguiente secuencia de comandos en cadena:

```bash
python3 send_uart.py ..mdio_w "phyaddr\x07" "regaddr\x0D" "mdio_d\x00\x02" mdio_sta "regaddr\x0E" "mdio_d\x00\x00" mdio_sta "regaddr\x0D" "mdio_d\x40\x02" mdio_sta "regaddr\x0E" "mdio_d\x00\x08" mdio_sta "regaddr\x0D" "mdio_d\x00\x02" mdio_sta "regaddr\x0E" "mdio_d\x00\x04" mdio_sta "regaddr\x0D" "mdio_d\x40\x02" mdio_sta "regaddr\x0E" "mdio_d\x00\xFC" mdio_sta "regaddr\x0D" "mdio_d\x00\x02" mdio_sta "regaddr\x0E" "mdio_d\x00\x05" mdio_sta "regaddr\x0D" "mdio_d\x40\x02" mdio_sta "regaddr\x0E" "mdio_d\x7F\xFF" mdio_sta "regaddr\x0D" "mdio_d\x00\x02" mdio_sta "regaddr\x0E" "mdio_d\x00\x06" mdio_sta "regaddr\x0D" "mdio_d\x40\x02" mdio_sta "regaddr\x0E" "mdio_d\xCC\xCC" mdio_sta "regaddr\x0D" "mdio_d\x00\x02" mdio_sta "regaddr\x0E" "mdio_d\x00\x08" mdio_sta "regaddr\x0D" "mdio_d\x40\x02" mdio_sta "regaddr\x0E" "mdio_d\x00\x4C" mdio_sta
```
*Confirmación visual:* El LED 3 (PLL) cambiará su intensidad y brillará igual que el LED 1 y 2.

### 2.3 Validación ARP (En el PC Host)
Verificar la conectividad MAC/IP:

```bash
sudo arping -I eth0 192.168.1.12
```

---
Si hay respuesta, fijar la MAC estáticamente en el Kernel del PC para evitar tormentas ARP durante las pruebas de alto rendimiento:
​
```bash
sudo arp -s 192.168.1.12 66:70:67:61:3A:30
```

---
## 3. Preparación de Transmisión (TX)

### 3.1 Parámetros de Disparo (Payload y Cantidad)
```bash
# Tamaño del Payload (MTU UDP). Rango: 64B a 1440B. Por defecto: 1440B.
python3 send_uart.py "udpmtu\x05\xA0"

# Cantidad de paquetes por trigger. Por defecto: 1. (Ejemplo para 1 Millón: 0x000F4240)
python3 send_uart.py "pktn\x00\x0F\x42\x40"

# Puertos UDP (Origen y Destino)
python3 send_uart.py "srport\x04\xD2" # Puerto 1234
python3 send_uart.py "dsport\x27\x0F" # Puerto 9999
```

### 3.2 Modos de Datos (Jerarquía de Payload)
Solo uno puede estar activo. La jerarquía de prioridad en hardware es: `Random` > `Constant` > `Secuencia`.
1.  **Aleatorio (`..random`):** Datos pseudoaleatorios vía Shift-Register/XOR.
2.  **Constante (`constant`):** Rellena el payload con caracteres 'X' (0x58).
3.  **Secuencia (Por defecto):** Desactivar los dos anteriores. Rellena contando de 0x00 a 0xFF sucesivamente.

### 3.3 Comandos de Ejecución
* `python3 send_uart.py .trigger` : Inicia la transmisión de ráfaga finita.
* `python3 send_uart.py ...flood` : Inicia transmisión continua (repetir comando para detener).
* `python3 send_uart.py loopback` : Activa/desactiva modo espejo (Rebota TX a RX).

---

## 4. Batería de Pruebas Estándar

Para validar completamente el hardware y firmware, ejecutar las siguientes pruebas en orden.

### Prueba 1: Rendimiento y Pérdida de Paquetes (Capa Física a UDP)
* **Objetivo:** Verificar desbordamientos en hardware (PHY/MAC) o software (Kernel).
* **Configuración FPGA:** Modo `.random`, 1 Millón de paquetes, Payload variable (64B, 512B, 1440B).
* **Metodología:** Ejecutar un script de captura (socket UDP con buffer aumentado) en el host. Enviar `.trigger`.
* **Criterio de Éxito:** Al finalizar la ráfaga, el script debe reportar 1,000,000 de paquetes. Si hay menos, cruzar datos con `ethtool -S eth0` y `nstat` para ubicar el cuello de botella.

### Prueba 2: Integridad de Payload
* **Objetivo:** Verificar corrupción de bits en la ruta de datos interna (FIFOs FPGA) y pistas de PCB.
* **Configuración FPGA:** Modo Secuencia (o `constant`), 1 Millón de paquetes, Payload 1440B.
* **Metodología:** Ejecutar script validador en Python. El script solo comprobará el Byte Inicial vs Byte Final de cada paquete. Enviar `.trigger`.
* **Criterio de Éxito:** 0 errores de cálculo en la secuencia de los payloads recibidos. 

### Prueba 3: Latencia y RTT (Round Trip Time)
* **Objetivo:** Medir tiempos de procesamiento interno.
* **Configuración FPGA:** `loopback`.
* **Metodología:** Usar script como `nping` o herramienta C customizada desde el PC Host. Medir RTT con diferentes tamaños de payload.
* **Criterio de Éxito:** Latencias sub-milisegundo estables, sin picos anómalos.

### Prueba 4: Estrés y Caída del Loopback
* **Objetivo:** Encontrar el límite máximo de procesamiento concurrente.
* **Configuración FPGA:** `loopback`.
* **Metodología:** PC Host inyecta tráfico UDP masivo y constante. Aumentar tasa de paquetes progresivamente.
* **Criterio de Éxito:** Identificar el punto de inflexión (paquetes por segundo) donde la FPGA o el PC Host comienzan a descartar tráfico. Documentar este límite como el máximo teórico del sistema.
