#include <stdio.h>
#include "pico/stdlib.h"
#include "drivers/timer.h"
#include "drivers/gpio.h"

#define LED_PIN 25

int main() {
    stdio_init_all();
    gpio_config(LED_PIN, GPIO_OUT);

    while (true) {
        uint64_t start = timer_get_us();
        gpio_write(LED_PIN, 1);
        timer_delay_ms(500);
        gpio_write(LED_PIN, 0);
        timer_delay_ms(1000);

        uint64_t elapsed = timer_elapsed_us(start);
        printf("Loop elapsed: %llu us\n", elapsed);
    }
}