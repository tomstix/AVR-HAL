#include "UART.h"

#include "util.h"

#include <avr/io.h>

void UART_init(const UART_config_t *config)
{
    // Reset UART registers
    UCSR0A = 0;
    UCSR0B = 0;
    UCSR0C = 0;

    // Set baud rate
    // Values are taken from the datasheet
    switch (config->baudrate)
    {
    case UART_4800:
        UBRR0 = 207;
        break;
    case UART_9600:
        UBRR0 = 103;
        break;
    case UART_19200:
        UBRR0 = 51;
        break;
    case UART_38400:
        UBRR0 = 25;
        break;
    case UART_57600:
        UBRR0 = 16;
        break;
    case UART_115200:
        UBRR0 = 8;
        break;
    }

    // Set data bits
    switch (config->data_bits)
    {
    case UART_5_BITS:
        UCSR0C = (1 << UCSZ00);
        break;
    case UART_6_BITS:
        UCSR0C = (1 << UCSZ01);
        break;
    case UART_7_BITS:
        UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
        break;
    case UART_8_BITS:
        UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
        break;
    }

    // Set stop bits
    switch (config->stop_bits)
    {
    case UART_1_STOP_BIT:
        UCSR0C &= ~(1 << USBS0);
        break;
    case UART_2_STOP_BITS:
        UCSR0C |= (1 << USBS0);
        break;
    }

    // Set parity
    switch (config->parity)
    {
    case UART_NO_PARITY:
        UCSR0C &= ~(1 << UPM01);
        UCSR0C &= ~(1 << UPM00);
        break;
    case UART_EVEN_PARITY:
        UCSR0C |= (1 << UPM01);
        UCSR0C &= ~(1 << UPM00);
        break;
    case UART_ODD_PARITY:
        UCSR0C |= (1 << UPM01);
        UCSR0C |= (1 << UPM00);
        break;
    }

    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

void UART_transmit_byte(const uint8_t data)
{
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)))
        ;

    // Put data into buffer, sends the data
    UDR0 = data;
}

void UART_transmit_string(const char *data)
{
    for (int i = 0; data[i] != '\0'; i++)
    {
        UART_transmit_byte(data[i]);
    }
}

void UART_transmit_HEX_byte(const uint8_t data)
{
    char buffer[2 + sizeof(uint8_t) * 2 + 1];
    buffer[0] = '0';
    buffer[1] = 'x';
    char_to_hex_str(data, buffer + 2);
    UART_transmit_string(buffer);
}

void UART_transmit_HEX_int(const int data)
{
    char buffer[2 + sizeof(int) * 2 + 1];
    buffer[0] = '0';
    buffer[1] = 'x';
    int_to_hex_str(data, buffer + 2);
    UART_transmit_string(buffer);
}

void UART_transmit_HEX_long(const long data)
{
    char buffer[2 + sizeof(long) * 2 + 1];
    buffer[0] = '0';
    buffer[1] = 'x';
    long_to_hex_str(data, buffer + 2);
    UART_transmit_string(buffer);
}

void UART_transmit_DEC_int(const uint32_t data)
{
    char buffer[sizeof(uint32_t) * 3 + 1];
    int_to_dec_str(data, buffer);
    UART_transmit_string(buffer);
}

uint8_t UART_receive_byte(void)
{
    // Wait for data to be received
    while (!(UCSR0A & (1 << RXC0)))
        ;

    // Get and return received data from buffer
    return UDR0;
}

void UART_enable_receive_interrupt(void)
{
    // Enable the USART Receive Complete interrupt
    UCSR0B |= _BV(RXCIE0);
    asm("sei");
}