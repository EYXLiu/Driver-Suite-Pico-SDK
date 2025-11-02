#include "drivers/pwm.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

void pwm_config_init(uint pin, uint freq_hz) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    
    uint32_t clock_freq = clock_get_hz(clk_sys);

    uint32_t divider16 = clock_freq / freq_hz / 65536 + 1;
    float divider = divider16 / 16.0f;

    uint32_t wrap = clock_freq / (freq_hz * divider) - 1;

    pwm_set_clkdiv(slice_num, divider);
    pwm_set_wrap(slice_num, wrap);

    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pin), 0);
    pwm_set_enabled(slice_num, true);
}

uint16_t pwm_get_wrap(uint pin) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    return pwm_hw->slice[slice_num].top;
}

uint16_t pwm_get_chan_level_pin(uint pin) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint channel = pwm_gpio_to_channel(pin);

    uint32_t cc = pwm_hw->slice[slice_num].cc;
    return channel == PWM_CHAN_B ? (cc >> PWM_CH0_CC_B_LSB) & 0xFFFF : (cc & 0xFFFF);
}

uint16_t pwm_get_chan_level(uint slice_num, uint channel) {
    uint32_t cc = pwm_hw->slice[slice_num].cc;
    return channel == PWM_CHAN_B ? (cc >> PWM_CH0_CC_B_LSB) & 0xFFFF : (cc & 0xFFFF);
}

float pwm_get_clkdiv_pin(uint pin) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint32_t div_reg = pwm_hw->slice[slice_num].div;

    return (float)(div_reg >> 8) + ((div_reg & 0xFF) / 256.0f);
}

float pwm_get_clkdiv(uint slice_num) {
    uint32_t div_reg = pwm_hw->slice[slice_num].div;

    return (float)(div_reg >> 8) + ((div_reg & 0xFF) / 256.0f);
}

void pwm_set_duty(uint pin, float duty_percent) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint channel = pwm_gpio_to_channel(pin);

    uint16_t wrap = pwm_hw->slice[slice_num].top;
    uint16_t level = (uint16_t)((duty_percent / 100.0f) * wrap);
    pwm_set_chan_level(slice_num, channel, level);
}

float pwm_get_duty(uint pin) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint channel = pwm_gpio_to_channel(pin);

    uint16_t wrap = pwm_hw->slice[slice_num].top;
    uint16_t level = pwm_get_chan_level(slice_num, channel);

    return ((float)level / (float)wrap) * 100.0f;
}

void pwm_set_freq(uint pin, uint freq_hz) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint16_t wrap = pwm_hw->slice[slice_num].top;
    uint32_t clock_freq = clock_get_hz(clk_sys);

    float divider = pwm_get_clkdiv(slice_num);
    wrap = clock_freq / (freq_hz * divider) - 1;
    
    pwm_set_wrap(slice_num, wrap);
}

void pwm_enable_pin(uint pin) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_enabled(slice_num, true);
}

void pwm_disable_pin(uint pin) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_enabled(slice_num, false);
}

void pwm_set_raw(uint slice_num, uint16_t wrap, uint16_t level) {
    pwm_set_wrap(slice_num, wrap);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, level);
}
