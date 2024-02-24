#include "spi.h"

#include <avr/io.h>

void spi_master_init(void)
{
    DDRB |= (1 << DDB3) | (1 << DDB5) | (1 << DDB2);
    SPCR |= (1 << MSTR) | (1 << SPE);
}

void spi_master_tx_byte(const uint8_t data)
{
    SPDR = data;
    while (!(SPSR & (1 << SPIF)))
        ;
}

uint8_t spi_master_rx_byte(void)
{
    SPDR = 0x00;
    while (!(SPSR & (1 << SPIF)))
        ;
    return SPDR;
}
