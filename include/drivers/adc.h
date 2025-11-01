#ifndef ADC_H
#define ADC_H

#include "pico/stdlib.h"

void adc_config(uint channel);
void adc_select_channel(uint channel);

uint16_t adc_read_value(void);
uint16_t adc_read_channel(uint channel);
uint16_t adc_read_avg(uint channel, uint8_t samples);
float adc_read_voltage(uint channel);

float adc_read_temp(void);
float adc_read_vref(void);

#endif