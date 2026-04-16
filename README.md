# PIR Alarm System 🚨

A motion-activated alarm built with STM32 Nucleo F411RE.

## Hardware
- STM32 Nucleo F411RE
- PIR Motion Sensor (Keyestudio)
- LED
- Active Buzzer 5V (coming soon)

## Wiring
| Component | Nucleo Pin |
|-----------|-----------|
| PIR Signal | PA0 (A0) |
| LED | PA1 (A1) |
| Buzzer | PA2 (D1) |

## How It Works
- PIR sensor detects motion
- LED blinks 5 times as alarm
- Buzzer beeps (when connected)

## Status
-  PIR sensor working
-  LED working
-  Buzzer — pending replacement

## Built With
- STM32CubeIDE
- C (bare metal, no HAL)
