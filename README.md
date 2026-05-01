```markdown
# PIR Motion Alarm System — STM32 Nucleo F411RE

A bare-metal PIR motion detection alarm system built on the STM32 Nucleo F411RE using direct register manipulation (no HAL).

When motion is detected, the LED and buzzer trigger together in a fast blink pattern. Motion events are also logged over UART so you can monitor activity in real time from your computer.

---

## Hardware

- STM32 Nucleo F411RE
- PIR motion sensor
- LED + 330Ω resistor
- Active buzzer

---

## Pin Connections

| Component     | Pin  | Notes                        |
|---------------|------|------------------------------|
| PIR sensor    | PA0  | Digital input                |
| LED + Buzzer  | PA1  | Output, shared pin           |
| UART TX (log) | PA2  | Connected to ST-Link via USB |

---

## How It Works

- **PA0** reads the PIR sensor output
- On motion detected, PA1 pulses HIGH/LOW 5 times (200ms on, 200ms off)
- **UART2** sends `Motion detected!` and `No motion` messages at 9600 baud over the USB cable
- No motion → all outputs off

---

## UART Logging

To monitor motion events connect to the Nucleo's virtual COM port:

- **Baud rate:** 9600
- **Port:** `/dev/tty.usbmodem...` on Mac, `COMx` on Windows
- Use CoolTerm (Mac) or PuTTY (Windows)

Output example:

System ready
Motion detected!
No motion
Motion detected!

---

## Registers Used

| Register       | Address      | Purpose              |
|----------------|--------------|----------------------|
| RCC_AHB1ENR    | 0x40023830   | Enable GPIOA clock   |
| RCC_APB1ENR    | 0x40023840   | Enable USART2 clock  |
| GPIOA_MODER    | 0x40020000   | Pin mode config      |
| GPIOA_ODR      | 0x40020014   | Output data register |
| GPIOA_IDR      | 0x40020010   | Input data register  |
| USART2_BRR     | 0x40004408   | Baud rate register   |
| USART2_CR1     | 0x4000440C   | UART control         |

---

## Build

Open in STM32CubeIDE as an existing project. No HAL or middleware — pure bare-metal C with direct register access.

---

## Author

Mussie Mengsteab — [github.com/musee-00](https://github.com/musee-00)
```