#include <stdio.h>
#include "pico/stdlib.h"
#include "gpio.h"

#define LED_PIN 25

int main() {
    stdio_init_all(); 
    gpio_config(LED_PIN, GPIO_OUTPUT);

    while (true) {
        gpio_write(LED_PIN, 1);
        sleep_ms(500);
        gpio_write(LED_PIN, 0);
        sleep_ms(500);
    }
}