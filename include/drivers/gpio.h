#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef enum {
    GPIO_PULL_NONE,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN
} gpio_pull_t;

void gpio_config(uint8_t pin, gpio_mode_t mode);
void gpio_write(uint8_t pin, uint8_t value);
uint8_t gpio_read(uint8_t pin);

void gpio_set_func(uint8_t pin, gpio_func_t func);

void gpio_set_pull(uint8_t, gpio_pull_t pull);

#endif