#include <stdint.h>

#define RCC_AHB1ENR   (*((volatile uint32_t *)0x40023830))
#define RCC_APB1ENR   (*((volatile uint32_t *)0x40023840))
#define GPIOA_MODER   (*((volatile uint32_t *)0x40020000))
#define GPIOA_ODR     (*((volatile uint32_t *)0x40020014))
#define GPIOA_IDR     (*((volatile uint32_t *)0x40020010))
#define GPIOA_AFRL    (*((volatile uint32_t *)0x40020020))
#define USART2_SR     (*((volatile uint32_t *)0x40004400))
#define USART2_DR     (*((volatile uint32_t *)0x40004404))
#define USART2_BRR    (*((volatile uint32_t *)0x40004408))
#define USART2_CR1    (*((volatile uint32_t *)0x4000440C))

void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 4000; i++);
}

void uart_init(void) {
    // Enable USART2 clock
    RCC_APB1ENR |= (1U << 17);

    // PA2 = Alternate function (USART2 TX)
    GPIOA_MODER &= ~(3U << 4);
    GPIOA_MODER |=  (2U << 4);  // AF mode

    // Set AF7 (USART2) on PA2
    GPIOA_AFRL &= ~(0xF << 8);
    GPIOA_AFRL |=  (7U << 8);

    // Baud rate 9600 @ 16MHz HSI
    // BRR = 16000000 / 9600 = 1667 = 0x683
    USART2_BRR = 0x683;

    // Enable USART2, TX only
    USART2_CR1 = (1U << 13) | (1U << 3);
}

void uart_send_char(char c) {
    while (!(USART2_SR & (1U << 7)));  // wait for TX ready
    USART2_DR = c;
}

void uart_send_string(const char *s) {
    while (*s) {
        uart_send_char(*s++);
    }
}

int main(void) {
    RCC_AHB1ENR |= (1U << 0);

    uart_init();

    // PA1 = Output (LED + Buzzer)
    GPIOA_MODER &= ~(3U << 2);
    GPIOA_MODER |=  (1U << 2);

    // PA0 = Input (PIR)
    GPIOA_MODER &= ~(3U << 0);

    uart_send_string("System ready\r\n");

    uint8_t last_state = 0;

    while (1) {
        if (GPIOA_IDR & (1U << 0)) {
            if (!last_state) {
                // Only log on first detection, not every loop
                uart_send_string("Motion detected!\r\n");
                last_state = 1;
            }
            for (int i = 0; i < 5; i++) {
                GPIOA_ODR |=  (1U << 1);
                delay_ms(200);
                GPIOA_ODR &= ~(1U << 1);
                delay_ms(200);
            }
        } else {
            if (last_state) {
                uart_send_string("No motion\r\n");
                last_state = 0;
            }
            GPIOA_ODR &= ~(1U << 1);
        }
        delay_ms(100);
    }
}
