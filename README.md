# PIR Alarm System — STM32F411RE

Motion-activated alarm built with bare-metal register control. No HAL dependencies — all GPIO configured directly through memory-mapped registers.

---

## What It Does

- Reads PIR sensor signal on PA0
- On motion detected: blinks LED on PA1 five times as alarm
- Buzzer on PA2 wired and ready — pending hardware replacement

---

## Hardware

- STM32 Nucleo F411RE
- PIR Motion Sensor (Keyestudio)
- LED
- Active Buzzer 5V (pending replacement)

| Component | Pin |
|-----------|-----|
| PIR Signal | PA0 |
| LED | PA1 |
| Buzzer | PA2 |

---

## How It Works

**Clock and GPIO setup**
```c
RCC_AHB1ENR |= (1U << 0);   // enable GPIOA clock

GPIOA_MODER |= (1U << 2);   // PA1 output (LED)
GPIOA_MODER |= (1U << 4);   // PA2 output (Buzzer)
GPIOA_MODER &= ~(3U << 0);  // PA0 input (PIR)
```

**Motion detection loop**
```c
if (GPIOA_IDR & (1U << 0)) {
    // blink LED 5 times
}
```

---

## Status

- PIR sensor working
- LED alarm working
- Buzzer — pending hardware replacement

---

## File Structure

| File | Purpose |
|------|---------|
| `Src/main.c` | Full implementation — GPIO setup and alarm loop |

---

## Build & Flash

Open in **STM32CubeIDE**, build with `Ctrl+B`, flash with `Run`.

---

## Stack

**C · STM32F411RE · ARM Cortex-M4 · Bare-metal · No HAL**
