#include "drivers/gpio.h"
#include "hardware/gpio.h"

void gpio_config(uint8_t pin, gpio_mode_t mode) {
    gpio_init(pin);
    gpio_set_dir(pin, mode == GPIO_OUTPUT ? true : false);

}
void gpio_write(uint8_t pin, uint8_t value) {
    gpio_put(pin, value);
}
uint8_t gpio_read(uint8_t pin) {
    return gpio_get(pin);
}

void gpio_set_function(uint8_t pin, gpio_func_t func) {
    switch (func) {
        case GPIO_FUNC_GPIO: gpio_set_function(pin, GPIO_FUNC_SIO); break;
        case GPIO_FUNC_SPI: gpio_set_function(pin, GPIO_FUNC_SPI); break;
        case GPIO_FUNC_UART: gpio_set_function(pin, GPIO_FUNC_UART); break;
        case GPIO_FUNC_I2C: gpio_set_function(pin, GPIO_FUNC_I2C); break;
        case GPIO_FUNC_PWM: gpio_set_function(pin, GPIO_FUNC_PWM); break;
    }
}

void gpio_set_pull(uint8_t pin, gpio_pull_t pull) {
    switch (pull) {
        case GPIO_PULL_NONE: gpio_disable_pulls(pin); break;
        case GPIO_PULL_UP: gpio_pull_up(pin); break;
        case GPIO_PULL_DOWN: gpio_pull_down(pin); break;
    }
}
