#include "drivers/system.h"
#include "hardware/clocks.h"
#include "hardware/resets.h"
#include "hardware/watchdog.h"

void system_config(void) {
    set_sys_clock_khz(12500, true); //125mhz
}

void system_enable_peripheral(uint peripheral_id, bool enable) {
    if (enable) unreset_block(peripheral_id);
    else reset_block(peripheral_id);
}

void system_reset_peripheral(uint peripheral_id) {
    reset_block(peripheral_id);
    unreset_block(peripheral_id);
}

void system_set_cpu_freq(uint freq_hz) {
    if (freq_hz == 250000000) set_sys_clock_pll(250, 1);
    else set_sys_clock_khz(12500, true);
}

void system_enable_watchdog(uint timeout_ms) {
    watchdog_enable(timeout_ms, true);
}

void system_disable_watchdog(void) {
    watchdog_disable();
}