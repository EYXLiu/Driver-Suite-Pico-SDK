#include "drivers/gpio.h"
#include "hardware/gpio.h"

void gpio_config(uint8_t pin, bool mode) {
    gpio_init(pin);
    gpio_set_dir(pin, mode);

}
void gpio_write(uint8_t pin, uint8_t value) {
    gpio_put(pin, value);
}
uint8_t gpio_read(uint8_t pin) {
    return gpio_get(pin);
}

void gpio_set_func(uint8_t pin, gpio_func_t func) {
    gpio_set_function(pin, func);
}

void gpio_set_pull(uint8_t pin, gpio_pull_t pull) {
    switch (pull) {
        case GPIO_PULL_NONE: gpio_disable_pulls(pin); break;
        case GPIO_PULL_UP: gpio_pull_up(pin); break;
        case GPIO_PULL_DOWN: gpio_pull_down(pin); break;
    }
}
