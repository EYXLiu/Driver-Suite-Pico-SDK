#include "drivers/adc.h"
#include "hardware/adc.h"
#include "hardware/regs/adc.h"

void adc_config(uint channel) {
    adc_init();
    adc_gpio_init(26 + channel);
    adc_select_input(channel);
}

void adc_select_channel(uint channel) {
    adc_select_input(channel);
}

uint16_t adc_read_value(void) {
    return adc_read();
}

uint16_t adc_read_channel(uint channel) {
    adc_select_input(channel);
    return adc_read();
}

uint16_t adc_read_avg(uint channel, uint8_t samples) {
    adc_select_input(channel);
    uint32_t sum = 0;
    for (uint8_t i = 0; i < samples; i++) {
        sum += adc_read();
    }
    return sum / samples;
}

float adc_read_voltage(uint channel) {
    adc_select_input(channel);
    uint16_t val = adc_read();
    return val * 3.3f / 4095.0f; // for 3.3V
}

float adc_read_temp(void) {
    adc_select_input(4);
    uint16_t raw = adc_read();
    float v = raw * 3.3f / 4095.0f;
    return 27.0f - (v - 0.706f) / 0.001721f;
}

float adc_read_vref(void) {
    adc_select_input(4);
    return 3.3f; // normally 3.3V, would need external calibration
}
