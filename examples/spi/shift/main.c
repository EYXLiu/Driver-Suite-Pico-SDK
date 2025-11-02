#include <stdio.h>
#include "pico/stdlib.h"
#include "drivers/spi.h"
#include "drivers/gpio.h"

#define SPI_PORT spi0
#define PIN_SCK 2
#define PIN_MOSI 3
#define PIN_MISO 4
#define PIN_LATCH 5
#define PIN_CS 5

void latch_pulse(uint pin) {
  gpio_write(pin, 1);
  sleep_us(1);
  gpio_write(pin, 0);
}

int main() {
  stdio_init_all();
  spi_config(SPI_PORT, PIN_SCK, PIN_MOSI, PIN_MISO, PIN_CS, 1000*1000, 0);

  gpio_config(PIN_LATCH, GPIO_OUT);
  gpio_write(PIN_LATCH, 0);

  uint8_t data = 0x01;

  while (true) {
    spi_write(SPI_PORT, &data, 1);

    latch_pulse(PIN_LATCH);
    
    printf("Output pattern: 0x%02X\n", data);
    
    data = (data << 1);
    if (data == 0) data = 0x01;

    sleep_ms(300);

  }
}