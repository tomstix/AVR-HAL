#include "i2c.h"

#include <util/twi.h>

#include "delay.h"

void i2c_init(i2c_freq_t freq) {
  TWSR = 0;          // prescaler = 1
  TWBR = freq;       // set bit rate register
  TWCR = _BV(TWEN);  // enable I2C
}

static void i2c_wait(void) {
  while ((TWCR & _BV(TWINT)) == 0)
    ;
}

void i2c_start(void) {
  // send start condition
  TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWSTA);
  // wait for start condition to be transmitted
  i2c_wait();
}

void i2c_stop(void) {
  // send stop condition
  TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWSTO);
  // wait for stop condition to be transmitted
  while (!(TWCR & _BV(TWSTO)))
    ;
}

uint8_t i2c_get_status(void) {
  // read status bits
  uint8_t status = TWSR & TW_STATUS_MASK;
  return status;
}

void i2c_tx(uint8_t data) {
  // load data into data register
  TWDR = data;
  // start transmission of data
  TWCR = _BV(TWEN) | _BV(TWINT);
  // wait for transmission to complete
  i2c_wait();
}

uint8_t i2c_rx_ack(void) {
  // start TWI and wait for data
  TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);
  i2c_wait();
  // return received data
  return TWDR;
}

uint8_t i2c_rx_nack(void) {
  // start receiving without acknowledging reception
  TWCR = _BV(TWEN) | _BV(TWINT);
  i2c_wait();
  // return received data
  return TWDR;
}

i2c_err_t i2c_read_reg(uint8_t addr, uint8_t reg, uint8_t *data) {
  uint8_t val;
  i2c_start();
  if (i2c_get_status() != TW_START) {
    return I2C_ERROR;
  }
  i2c_tx((uint8_t)(addr << 1));
  if (i2c_get_status() != TW_MT_SLA_ACK) {
    return I2C_ERROR;
  }
  i2c_tx(reg);
  if (i2c_get_status() != TW_MT_DATA_ACK) {
    return I2C_ERROR;
  }
  i2c_stop();
  delay_us(1);

  i2c_start();
  if (i2c_get_status() != TW_START) {
    return I2C_ERROR;
  }
  i2c_tx((uint8_t)((addr << 1) | 1));
  if (i2c_get_status() != TW_MR_SLA_ACK) {
    return I2C_ERROR;
  }
  val = i2c_rx_nack();
  if (i2c_get_status() != TW_MR_DATA_NACK) {
    return I2C_ERROR;
  }
  i2c_stop();
  *data = val;
  delay_us(100);
  return I2C_OK;
}

i2c_err_t i2c_write_reg(uint8_t addr, uint8_t reg, uint8_t data) {
  i2c_start();
  if (i2c_get_status() != TW_START) {
    return I2C_ERROR;
  }
  i2c_tx((uint8_t)(addr << 1));
  if (i2c_get_status() != TW_MT_SLA_ACK) {
    return I2C_ERROR;
  }
  i2c_tx(reg);
  if (i2c_get_status() != TW_MT_DATA_ACK) {
    return I2C_ERROR;
  }
  i2c_tx(data);
  if (i2c_get_status() != TW_MT_DATA_ACK) {
    return I2C_ERROR;
  }
  i2c_stop();
  delay_us(100);
  return I2C_OK;
}