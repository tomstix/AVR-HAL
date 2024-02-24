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
} uart_config_t;

void uart_init(const uart_config_t *config);

void uart_tx_byte(const uint8_t data);

void uart_tx_string(const char *data);

void uart_tx_HEX_byte(const uint8_t data);

void uart_tx_HEX_int(const int data);

void uart_tx_HEX_long(const long data);

void uart_tx_DEC_int(const uint32_t data);

void uart_enable_rx_isr(void);

uint8_t uart_rx_byte(void);