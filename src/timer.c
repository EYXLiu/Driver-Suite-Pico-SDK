#include "drivers/timer.h"
#include "hardware/timer.h"

void timer_delay_ms(uint32_t ms) {
    sleep_ms(ms);
}

void timer_delay_us(uint32_t us) {
    sleep_us(us);
}

uint64_t timer_get_ms(void) {
    return time_us_64() / 1000;
}

uint64_t timer_get_us(void) {
    return time_us_64();
}

uint64_t timer_elapsed_us(uint64_t start) {
    return time_us_64() - start;
}

bool timer_expired_us(uint64_t start, uint64_t duration) {
    return time_us_64() - start >= duration;
}
