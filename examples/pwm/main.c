#include <stdio.h>
#include "pico/stdlib.h"
#include "drivers/pwm.h"

#define LED_PIN 15

int main() {
    stdio_init_all();
    pwm_config_init(LED_PIN, 1000);

    float duty = 0;

    while (true) {
        pwm_set_duty(LED_PIN, duty);
        duty += 10;
        if (duty > 100) duty = 0;

        sleep_ms(500);
    }
}