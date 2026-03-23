# FPGA UDP Communication Controller

## Overview
This project implements a UDP communication controller on FPGA with PHY management capabilities through MDIO interface. The system supports multiple operation modes and provides UART-based control interface.

## Hardware Features

### Indicators LEDs and Switches

| Switch | Function | LED Indicator | Description |
|--------|----------|---------------|-------------|
| SW[0] | Reset PHY | - | Hardware reset for PHY |
| SW[1] | LED power-off | LED[0] | Global reset_n |
| SW[1] | LED power-off | LED[1] | PHY reset_n |
| SW[2] | LED power-off | LED[2] | PHY PLL 125MHz clock |
| SW[3] | LED power-off | LED[3] | PHY interruption_n |
| SW[4] | LED power-off | LED[4] | UDP loopback mode |
| SW[5] | LED power-off | LED[5] | UDP random data mode |
| SW[6] | LED power-off | LED[6] | UDP sending preset data |
| SW[7] | LED power-off | LED[7] | MDIO busy |

### Push Buttons

| Button | Function |
|--------|----------|
| PUSH[0] | PHY reset |
| PUSH[1] | Reset UART and MDIO interfaces |
| PUSH[2] | Global reset |

## UDP Operation Modes

The system supports multiple UDP transmission modes:

- **Default Mode**: Standard UDP operation
- **Loopback Mode**: Echo received data back
- **Random Data Mode**: Generate and send random data packets
- **Preset Data Mode**: Send predefined data patterns

## UART Communication Protocol

### Configuration
- **Baud Rate**: 115200
- **Data Bits**: 8
- **Stop Bits**: 1
- **Parity**: None

### Command Structure

#### UDP Control Commands

| Command | Hex | Description |
|---------|-----|-------------|
| 'L' | 0x4C | Set loopback mode (activates LED[4]) |
| 'T' | 0x54 | Start a trigger pulse |
| 'R' | 0x52 | Set random data mode (activates LED[5]) |

#### PHY/MDIO Control Commands

| Command | Hex | Description |
|---------|-----|-------------|
| 'w' | 0x77 | MDIO write mode |
| 'r' | 0x72 | MDIO read mode |
| 8'b001AAAAA | - | Set 5-bit PHY address |
| 8'b100RRRRR | - | Set 5-bit register address |
| 'd' | 0x64 | Set write data mode (followed by MSB and LSB) |
| 's' | 0x73 | Send pulse to start MDIO operation |

### MDIO Transaction Sequence

1. **Set Mode**: Send 'r' (read) or 'w' (write)
2. **Set Address**: Configure PHY address (5 bits)
3. **Set Register**: Configure register address (5 bits)
4. **Set Data** (write only): Send 'd' followed by MSB and LSB
5. **Execute**: Send 's' to start MDIO operation

## Software Interface

### Python Control Script

```python
#!/usr/bin/env python3
import serial
import threading
import sys

ser = serial.Serial('/dev/ttyUSB0', 115200)

def recibir():
    """Background thread for receiving data"""
    while True:
        if ser.in_waiting:
            byte = ser.read(1)
            bits = format(byte[0], '08b')
            hex_val = format(byte[0], '02X')
            print(f"\rRecibido: bits={bits} hex=0x{hex_val}")

def enviar():
    """Send hex commands to FPGA"""
    print("Escribe bytes en hex (ej: 4C) o 'q' para salir:")
    while True:
        entrada = input("> ").strip()
        if entrada.lower() == 'q':
            ser.close()
            sys.exit(0)
        try:
            byte = bytes.fromhex(entrada)
            ser.write(byte)
            print(f"Enviado: {entrada.upper()}")
        except:
            print("Error: escribe un byte en hex (ej: 4C, FF, 00)")

# Start receiving thread
thread_receive = threading.Thread(target=recibir, daemon=True)
thread_receive.start()
enviar()
```
## Usage Example

1. Connect FPGA via USB and power on
2. Run the Python script:
```bash
python3 fpga_control.py
```
3. Send commands in hexadecimal format

### Command Chain Examples

**Read PHY Register (Default Configuration):**
```bash
72278073
```
This executes: read mode → PHY address 7 → register 0 → start read

**Write to PHY Register:**
```bash
722780737727806414407372
```
Where:
- 72278073: Set read mode, PHY 7, reg 0, start read
- 77278064: Set write mode, PHY 7, reg 0, data mode
- 14: MSB data (0x14)
- 40: LSB data (0x40)
- 73: Start write operation
- 72: Return to read mode

### Predefined Command Sequences

| Sequence | Description |
|----------|-------------|
| 7227807377278064114073727372 | Default configuration for PHY 7, register 0 |
| 7227807377278064914073727372 | Software reset for PHY 7 |
| 7227807377278064194073727372 | Power down for PHY 7 |
| 72278073 | Read PHY 7, register 0 |

## Safety Features

The command sequence follows a safety protocol:

1. Set read mode to verify current state
2. Configure target PHY and register
3. Set write data (if applicable)
4. Execute operation
5. Verify changes by reading back
6. Return to read mode for safety

## Troubleshooting

### Common Issues

| Issue | Solution |
|-------|----------|
| No response from FPGA | Check USB connection and power |
| LED indicators inactive | Verify switch configurations |
| MDIO busy (LED[7]) | Wait for operation to complete |
| Communication errors | Verify baud rate (115200) |

### LED Status Indicators

| LED | Description |
|-----|-------------|
| LED[0] | Global reset - active low |
| LED[1] | PHY reset - active low |
| LED[2] | PHY PLL locked |
| LED[3] | PHY interrupt |
| LED[4] | UDP loopback mode active |
| LED[5] | UDP random data mode active |
| LED[6] | UDP preset data transmission |
| LED[7] | MDIO busy |
