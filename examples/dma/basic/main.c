#include <stdio.h>
#include "pico/stdlib.h"
#include "drivers/dma.h"
#include "drivers/gpio.h"

#define LED_PIN 15

int main() {
    stdio_init_all();
    gpio_config(LED_PIN, GPIO_OUT);

    uint32_t src[5] = { 1, 2, 3, 4, 5 };
    uint32_t dst[5] = {0};

    int chan = dma_config(false);

    dma_start_transfer(chan, src, dst, 5);

    dma_wait_complete(chan);

    gpio_write(LED_PIN, 1);
    sleep_ms(500);
    gpio_write(LED_PIN, 0);

    printf("DMA transfer done. dst[] = ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", dst[i]);
    }
    printf("\n");

    while (true) {
        sleep_ms(250);
    }
}