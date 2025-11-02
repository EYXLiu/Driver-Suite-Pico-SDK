#include <stdio.h>
#include "pico/stdlib.h"
#include "drivers/dma.h"
#include "drivers/gpio.h"

#define NUM_LEDS 8
const uint led_pins[NUM_LEDS] = { 1, 2, 3, 4, 5, 6, 7, 8 };

int main() {
    stdio_init_all();

    for (int i = 0; i < NUM_LEDS; i++) {
        gpio_config(led_pins[i], GPIO_OUT);
    }

    uint32_t states1[NUM_LEDS] = { 1, 0, 1, 0, 1, 0, 1, 0 };
    uint32_t states2[NUM_LEDS] = { 0, 1, 0, 1, 0, 1, 0, 1 };
    uint32_t led_buffer[NUM_LEDS] = {0};

    int chan = dma_config(false);

    //normally would access gpio_hw->out to directly map, but cannot through sdk so need to create a buffer to light up the leds
    //dma_start_transfer(chan, &states, &gpio_hw->out, NUM_LEDS);
    //hardware/structs/gpio.h is not publically facing

    while (true) {
        dma_start_transfer(chan, &states1, &led_buffer, NUM_LEDS);
        dma_wait_complete(chan);
        
        for (int i = 0; i < NUM_LEDS; i++) {
            gpio_write(led_pins[i], led_buffer[i]);
        }

        sleep_ms(500);

        dma_start_transfer(chan, &states2, &led_buffer, NUM_LEDS);
        dma_wait_complete(chan);

        for (int i = 0; i < NUM_LEDS; i++) {
            gpio_write(led_pins[i], led_buffer[i]);
        }

        sleep_ms(500);
    }
}