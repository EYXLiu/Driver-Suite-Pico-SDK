#include <stdio.h>
#include "pico/stdio.h"
#include "drivers/i2c.h"

uint8_t bcd2dec(uint8_t val) { return ((val >> 4) * 10) + (val & 0x0F); }
uint8_t dec2bcd(uint8_t val) { return ((val / 10) << 4) | (val % 10); }

#define DS1307_ADDR 0x68

int main() {
  stdio_init_all();
  i2c_config(i2c0, 4, 5, 100000);

  i2c_write_reg(i2c0, DS1307_ADDR, 0x00, dec2bcd(0));
  i2c_write_reg(i2c0, DS1307_ADDR, 0x01, dec2bcd(0));
  i2c_write_reg(i2c0, DS1307_ADDR, 0x02, dec2bcd(18));
  i2c_write_reg(i2c0, DS1307_ADDR, 0x04, dec2bcd(1));
  i2c_write_reg(i2c0, DS1307_ADDR, 0x05, dec2bcd(11));
  i2c_write_reg(i2c0, DS1307_ADDR, 0x06, dec2bcd(25));
  while (true) {
    uint8_t s = bcd2dec(i2c_read_reg(i2c0, DS1307_ADDR, 0x00));
    uint8_t m = bcd2dec(i2c_read_reg(i2c0, DS1307_ADDR, 0x01));
    uint8_t h = bcd2dec(i2c_read_reg(i2c0, DS1307_ADDR, 0x02));
    uint8_t d = bcd2dec(i2c_read_reg(i2c0, DS1307_ADDR, 0x03));
    uint8_t date = bcd2dec(i2c_read_reg(i2c0, DS1307_ADDR, 0x04));
    uint8_t mon = bcd2dec(i2c_read_reg(i2c0, DS1307_ADDR, 0x05));
    uint8_t yr = bcd2dec(i2c_read_reg(i2c0, DS1307_ADDR, 0x06));

    printf("Time: %02d:%02d:%02d Date: %02d/%02d/20%02d Day: %d\n", h, m, s, date, mon, yr, d);

    sleep_ms(1000);
  }
  
}