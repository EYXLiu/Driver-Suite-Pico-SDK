#include "drivers/spi.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"

void spi_config(spi_inst_t *spi_id, uint sck, uint mosi, uint miso, uint cs, uint baudrate, uint8_t spi_mode) {
    spi_init(spi_id, baudrate);
    gpio_set_function(sck, GPIO_FUNC_SPI);
    gpio_set_function(mosi, GPIO_FUNC_SPI);
    gpio_set_function(miso, GPIO_FUNC_SPI);

    gpio_init(cs);
    gpio_set_dir(cs, true);
    gpio_put(cs, 1);

    switch (spi_mode) {
        case 0: spi_set_format(spi_id, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST); break;
        case 1: spi_set_format(spi_id, 8, SPI_CPOL_0, SPI_CPHA_1, SPI_MSB_FIRST); break;
        case 2: spi_set_format(spi_id, 8, SPI_CPOL_1, SPI_CPHA_0, SPI_MSB_FIRST); break;
        case 3: spi_set_format(spi_id, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST); break;
        default: spi_set_format(spi_id, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST); break;
    }
}

void spi_select(uint cs) {
    gpio_put(cs, 0);
}

void spi_deselect(uint cs) {
    gpio_put(cs, 1);
}

uint8_t spi_transfer_byte(spi_inst_t *spi_id, uint8_t data) {
    uint8_t rx;
    spi_write_read_blocking(spi_id, &data, &rx, 1);
    return rx;
}

void spi_write(spi_inst_t *spi_id, uint8_t *data, size_t len) {
    spi_write_blocking(spi_id, data, len);
}

void spi_read(spi_inst_t *spi_id, uint8_t *data, size_t len) {
    uint8_t dummy = 0xFF;
    for (size_t i = 0; i< len; i++) {
        spi_write_read_blocking(spi_id, &dummy, &data[i], 1);
    }
}

void spi_transfer(spi_inst_t *spi_id, uint8_t *tx_data, uint8_t *rx_data, size_t len) {
    spi_write_read_blocking(spi_id, tx_data, rx_data, len);
}
