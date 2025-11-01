#include "drivers/i2c.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

void i2c_config(i2c_inst_t *i2c_id, uint sda, uint scl, uint baudrate) {
    i2c_init(i2c_id, baudrate);

    gpio_set_function(sda, GPIO_FUNC_I2C);
    gpio_set_function(scl, GPIO_FUNC_I2C);

    gpio_pull_up(sda);
    gpio_pull_up(scl);
}

void i2c_write_byte(i2c_inst_t *i2c_id, uint8_t addr, uint8_t data) {
    i2c_write_blocking(i2c_id, addr, &data, 1, false);
}

uint8_t i2c_read_byte(i2c_inst_t *i2c_id, uint8_t addr) {
    uint8_t data;
    i2c_read_blocking(i2c_id, addr, &data, 1, false);
    return data;
}

void i2c_write(i2c_inst_t *i2c_id, uint8_t addr, uint8_t *data, size_t len) {
    i2c_write_blocking(i2c_id, addr, data, len, false);
}

void i2c_read(i2c_inst_t *i2c_id, uint8_t addr, uint8_t *data, size_t len) {
    i2c_read_blocking(i2c_id, addr, data, len, false);
}

void i2c_write_reg(i2c_inst_t *i2c_id, uint8_t addr, uint8_t reg, uint8_t data) {
    uint8_t buf[2] = {reg, data};
    i2c_write_blocking(i2c_id, addr, buf, 2, false);
}

uint8_t i2c_read_reg(i2c_inst_t *i2c_id, uint8_t addr, uint8_t reg) {
    i2c_write_blocking(i2c_id, addr, &reg, 1, true);
    uint8_t data;
    i2c_read_blocking(i2c_id, addr, &data, 1, false);
    return data;
}

void i2c_write_reg_block(i2c_inst_t *i2c_id, uint8_t addr, uint8_t reg, uint8_t *data, size_t len) {
    uint8_t buf[len + 1];
    buf[0] = reg;
    for (size_t i = 0; i < len; i++) buf[i + 1] = data[i];
    i2c_write_blocking(i2c_id, addr, buf, len + 1, false);
}

void i2c_read_reg_block(i2c_inst_t *i2c_id, uint8_t addr, uint8_t reg, uint8_t *data, size_t len) {
    i2c_write_blocking(i2c_id, addr, &reg, 1, true);
    i2c_read_blocking(i2c_id, addr, data, len, false);
}
