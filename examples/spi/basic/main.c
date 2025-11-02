#include <stdio.h>
#include "pico/stdlib.h"
#include "drivers/spi.h"

#define SPI_PORT spi0
#define PIN_SCK 2
#define PIN_MOSI 3
#define PIN_MISO 4
#define PIN_CS 5

int main() {
    stdio_init_all();
    spi_config(SPI_PORT, PIN_SCK, PIN_MOSI, PIN_MISO, PIN_CS, 1000*1000, 0);

    while (true) {
        spi_select(PIN_CS);
        uint8_t tx = 0xA5;
        uint8_t rx = spi_transfer_byte(SPI_PORT, tx);
        spi_deselect(PIN_CS);

        printf("Sent: 0x%02X, Received 0x%02X\n", tx, rx);

        sleep_ms(1000);
    }
}