#ifndef DMA_H
#define DMA_H

#include "pico/stdlib.h"

int dma_config(bool high_priority);

void dma_start_transfer(int chan, const void *src, void *dst, uint32_t count);
bool dma_is_busy(int chan);
void dma_wait_complete(int chan);

void dma_configure_peripheral(int chan, const volatile void *src, volatile void *dst, uint32_t transfer_count, bool read_from_peripheral);

#endif