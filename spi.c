#include "spi.h"

#include <avr/io.h>

void spi_master_init(void) {
  DDRB |= (1 << DDB3) | (1 << DDB5) | (1 << DDB2);
  SPCR |= (1 << MSTR) | (1 << SPE) | (1 << SPR0) | (1 << CPHA);
}

void spi_master_tx_byte(const uint8_t data) {
  SPDR = data;
  /*
   * Taken from the Arduino SPI library:
   * The following NOP introduces a small delay that can prevent the wait
   * loop from iterating when running at the maximum speed. This gives
   * about 10% more speed, even if it seems counter-intuitive. At lower
   * speeds it is unnoticed.
   */
  asm volatile("nop");
  while (!(SPSR & (1 << SPIF)))
    ;
}

uint8_t spi_master_rx_byte(void) {
  SPDR = 0x00;
  while (!(SPSR & (1 << SPIF)))
    ;
  return SPDR;
}

uint8_t spi_master_tx_rx_byte(const uint8_t data) {
  SPDR = data;
  asm volatile("nop");
  while (!(SPSR & (1 << SPIF)))
    ;
  return SPDR;
}

void spi_enable_rx_interrupt(void) {
  SPCR |= (1 << SPIE);
  asm volatile("sei");
}
