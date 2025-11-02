#include "drivers/dma.h"
#include "hardware/dma.h"

int dma_config(bool high_priority) {
    int chan = dma_claim_unused_channel(true);
    dma_channel_config c = dma_channel_get_default_config(chan);
    channel_config_set_read_increment(&c, true);
    channel_config_set_write_increment(&c, true);
    channel_config_set_high_priority(&c, high_priority);
    dma_channel_configure(chan, &c, NULL, NULL, 0, false);
    return chan;
}

void dma_start_transfer(int chan, const void *src, void *dst, uint32_t count) {
    dma_channel_config c = dma_channel_get_default_config(chan);
    channel_config_set_read_increment(&c, true);
    channel_config_set_write_increment(&c, true);
    dma_channel_configure(chan, &c, dst, src, count, true);
}

bool dma_is_busy(int chan) {
    return dma_channel_is_busy(chan);
}

void dma_wait_complete(int chan) {
    dma_channel_wait_for_finish_blocking(chan);
}

void dma_configure_peripheral(int chan, const volatile void *src, volatile void *dst, uint32_t count, bool read_from_peripheral) {
    dma_channel_config c = dma_channel_get_default_config(chan);
    channel_config_set_read_increment(&c, !read_from_peripheral);
    channel_config_set_write_increment(&c, read_from_peripheral);
    dma_channel_configure(chan, &c, dst, src, count, true);
}
