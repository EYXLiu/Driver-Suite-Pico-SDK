#include "drivers/uart.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"

void uart_config(uart_inst_t *uart_id, uint tx_pin, uint rx_pin, uint baudrate) {
    uart_init(uart_id, baudrate);
    gpio_set_function(tx_pin, GPIO_FUNC_UART);
    gpio_set_function(rx_pin, GPIO_FUNC_UART);
}

void uart_write_byte(uart_inst_t *uart_id, uint8_t byte) {
    uart_putc(uart_id, byte);
}
uint8_t uart_read_byte(uart_inst_t *uart_id) {
    return uart_getc(uart_id);
}

void uart_write(uart_inst_t *uart_id, const char *str) {
    while (*str) uart_putc_raw(uart_id, *str++);
}

void uart_read(uart_inst_t *uart_id, char *buffer, int max_len) {
    int i = 0;
    char c;

    while (i < max_len - 1 && uart_is_readable(uart_id)) {
        c = uart_read_char(uart_id);
        if (c == '\n') break;
        buffer[i++] = c;
    }

    buffer[i] = '\0';
}
