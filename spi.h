#pragma once

#include <stdint.h>

void spi_master_init(void);

void spi_master_tx_byte(const uint8_t data);

uint8_t spi_master_rx_byte(void);
