#pragma once

#include <stdint.h>

// UART configuration, to be extended as needed
typedef struct
{
    enum {
        UART_4800,
        UART_9600,
        UART_19200,
        UART_38400,
        UART_57600,
        UART_115200
    } baudrate;
    enum {
        UART_5_BITS,
        UART_6_BITS,
        UART_7_BITS,
        UART_8_BITS
    } data_bits;
    enum {
        UART_1_STOP_BIT,
        UART_2_STOP_BITS
    } stop_bits;
    enum {
        UART_NO_PARITY,
        UART_EVEN_PARITY,
        UART_ODD_PARITY
    } parity;
} UART_config_t;

void UART_init(const UART_config_t *config);

void UART_tx_byte(const uint8_t data);

void UART_tx_string(const char *data);

void UART_tx_HEX_byte(const uint8_t data);

void UART_tx_HEX_int(const int data);

void UART_tx_HEX_long(const long data);

void UART_tx_DEC_int(const uint32_t data);

void UART_enable_rx_isr(void);

uint8_t UART_rx_byte(void);