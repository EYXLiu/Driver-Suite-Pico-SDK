#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef enum {
    GPIO_INPUT,
    GPIO_OUTPUT
} gpio_mode_t;

typedef enum {
    GPIO_LOW = 0,
    GPIO_HIGH = 1
} gpio_value_t;

typedef enum {
    GPIO_FUNC_GPIO,
    GPIO_FUNC_SPI,
    GPIO_FUNC_UART,
    GPIO_FUNC_I2C,
    GPIO_FUNC_PWM
} gpio_func_t;

typedef enum {
    GPIO_PULL_NONE,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN
} gpio_pull_t;

void gpio_config(uint8_t pin, gpio_mode_t mode);
void gpio_write(uint8_t pin, uint8_t value);
uint8_t gpio_read(uint8_t pin);

void gpio_set_function(uint8_t pin, gpio_func_t func);

void gpio_set_pull(uint8_t, gpio_pull_t pull);

#endif