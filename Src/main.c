#include <stdint.h>

#define RCC_AHB1ENR  (*((volatile uint32_t *)0x40023830))
#define GPIOA_MODER  (*((volatile uint32_t *)0x40020000))
#define GPIOA_ODR    (*((volatile uint32_t *)0x40020014))
#define GPIOA_IDR    (*((volatile uint32_t *)0x40020010))

void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 4000; i++);
}

int main(void) {
    RCC_AHB1ENR |= (1U << 0);

    // PA1 = Output (LED)
    GPIOA_MODER &= ~(3U << 2);
    GPIOA_MODER |=  (1U << 2);

    // PA2 = Output (Buzzer) — ready for when you get one!
    GPIOA_MODER &= ~(3U << 4);
    GPIOA_MODER |=  (1U << 4);

    // PA0 = Input (PIR)
    GPIOA_MODER &= ~(3U << 0);

    while (1) {
        if (GPIOA_IDR & (1U << 0)) {
            // Motion detected!
            // Fast blink LED 5 times as alarm
            for (int i = 0; i < 5; i++) {
                GPIOA_ODR |=  (1U << 1);  // LED ON
                // BUZZER LINE — uncomment when you get buzzer:
                // GPIOA_ODR |= (1U << 2);
                delay_ms(200);
                GPIOA_ODR &= ~(1U << 1);  // LED OFF
                //  BUZZER LINE — uncomment when you get buzzer:
                // GPIOA_ODR &= ~(1U << 2);
                delay_ms(200);
            }
        } else {
            // No motion — LED off
            GPIOA_ODR &= ~(1U << 1);
            GPIOA_ODR &= ~(1U << 2);
        }
        delay_ms(100);
    }
}
