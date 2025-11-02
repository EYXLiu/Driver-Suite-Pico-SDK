#include <stdio.h>
#include "pico/stdlib.h"
#include "drivers/adc.h"

int main() {
    stdio_init_all();
    adc_config(0);

    while (true) {
        float voltage = adc_read_voltage(0);
        printf("ADC Voltage: %.3f V\n", voltage);
        sleep_ms(500);
    }
}