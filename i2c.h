#pragma once

#include <stddef.h>
#include <stdint.h>

#define I2C_FREQ_100K (F_CPU / 100000UL - 16) / 2
#define I2C_FREQ_400K (F_CPU / 400000UL - 16) / 2

typedef uint8_t i2c_freq_t;

typedef enum { I2C_OK, I2C_ERROR } i2c_err_t;

void i2c_init(i2c_freq_t freq);

i2c_err_t i2c_read_reg(uint8_t addr, uint8_t reg, uint8_t *data);

i2c_err_t i2c_write_reg(uint8_t addr, uint8_t reg, uint8_t data);

i2c_err_t i2c_write_multi(uint8_t addr, uint8_t reg, const uint8_t *data,
                          size_t len);
