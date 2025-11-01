#include <stdio.h>
#include "pico/stdlib.h"
#include "drivers/uart.h"

int main() {
    stdio_init_all();

    uart_config(uart0, 0, 1, 115200);

    char buffer[100];
    uart_write(uart0, "Hello from uart\n");

    while (true) {
        if (uart_is_readable(uart0)) {
            uart_read(uart0, buffer, sizeof(buffer));
            uart_write(uart0, "Received: ");
            uart_write(uart0, buffer);
            uart_write(uart0, "\n");
        }
        sleep_ms(1000);
    }
}