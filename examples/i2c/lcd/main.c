#include <stdio.h>
#include "pico/stdio.h"
#include "drivers/i2c.h"

#define LCD_ADDR 0x27
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE 0x04
#define LCD_RS 0x01

void lcd_send(uint8_t data, bool rs) {
    uint8_t high = data & 0xF0;
    uint8_t low = (data << 4) & 0xF0;

    i2c_write_byte(i2c0, LCD_ADDR, high | (rs ? LCD_RS : 0) | LCD_BACKLIGHT);
    i2c_write_byte(i2c0, LCD_ADDR, high | (rs ? LCD_RS : 0) | LCD_BACKLIGHT | LCD_ENABLE);
    i2c_write_byte(i2c0, LCD_ADDR, high | (rs ? LCD_RS : 0) | LCD_BACKLIGHT);

    i2c_write_byte(i2c0, LCD_ADDR, low | (rs ? LCD_RS : 0) | LCD_BACKLIGHT);
    i2c_write_byte(i2c0, LCD_ADDR, low | (rs ? LCD_RS : 0) | LCD_BACKLIGHT | LCD_ENABLE);
    i2c_write_byte(i2c0, LCD_ADDR, low | (rs ? LCD_RS : 0) | LCD_BACKLIGHT);
}

void lcd_command(uint8_t cmd) { lcd_send(cmd, false); }
void lcd_write_char(uint8_t c) { lcd_send(c, true); }

void lcd_set_cursor(uint8_t col, uint8_t row) {
    const uint8_t row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
    lcd_command(0x80 | (col + row_offsets[row])); 
}

void lcd_init() {
    sleep_ms(50);

    lcd_command(0x33);
    lcd_command(0x32);
    lcd_command(0x28);
    lcd_command(0x0C);
    lcd_command(0x06);
    lcd_command(0x01);
    sleep_ms(5);
}

void lcd_print(char *str, uint8_t row) {
    lcd_set_cursor(0, row);
    for (int i = 0; str[i] && i < 20; i++) {
        lcd_write_char(str[i]);
    }
}

int main() {
    stdio_init_all();
    i2c_config(i2c0, 4, 5, 100000);
    lcd_init();

    lcd_print("Hello world", 0);
    lcd_print("Demo", 1);
    lcd_print("Line 3", 2);
    lcd_print("Line 4", 3);

    while (true) {
        sleep_ms(1000);
    }
}
