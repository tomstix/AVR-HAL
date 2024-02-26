#pragma once

#include <stdint.h>
#include <stddef.h>

void byte_to_hex(uint8_t byte, char *hex)
{
    uint8_t nibble = (byte >> 4) & 0x0F;
    *hex = nibble < 10 ? '0' + nibble : 'A' + nibble - 10;
    nibble = byte & 0x0F;
    *(hex + 1) = nibble < 10 ? '0' + nibble : 'A' + nibble - 10;
}

void any_to_hex_str(const void *data, size_t size, char *hex)
{
    for (size_t i = 0; i < size; i++)
    {
        byte_to_hex(((const uint8_t *)data)[i], hex + 2 * i);
    }
    // Reverse the string because the hex is little endian
    for (size_t i = 0; i < size / 2; i++)
    {
        char temp = hex[2 * i];
        hex[2 * i] = hex[2 * size - 2 * i - 2];
        hex[2 * size - 2 * i - 2] = temp;
        temp = hex[2 * i + 1];
        hex[2 * i + 1] = hex[2 * size - 2 * i - 1];
        hex[2 * size - 2 * i - 1] = temp;
    }
    hex[2 * size] = '\0';
}

void char_to_hex_str(char value, char *hex)
{
    byte_to_hex(value, hex);
    hex[2] = '\0';
}

void int_to_hex_str(int value, char *hex)
{
    for (size_t i = 0; i < sizeof(int); i++)
    {
        byte_to_hex((value >> (8 * (sizeof(int) - i - 1))) & 0xFF, hex + 2 * i);
    }
    hex[2 * sizeof(int)] = '\0';
}

void long_to_hex_str(long value, char *hex)
{
    for (size_t i = 0; i < sizeof(long); i++)
    {
        byte_to_hex((value >> (8 * (sizeof(long) - i - 1))) & 0xFF, hex + 2 * i);
    }
    hex[2 * sizeof(long)] = '\0';
}

void int_to_dec_str(int32_t value, char *dec)
{
    if (value < 0)
    {
        *dec = '-';
        dec++;
        value = -value;
    }
    int32_t divisor = 1000000000;
    int32_t quotient = value;
    int32_t remainder;
    const char *start = dec;
    while (divisor > 0)
    {
        remainder = quotient / divisor;
        quotient = quotient % divisor;
        if (remainder > 0 || start != dec)
        {
            *dec = '0' + (char)remainder;
            dec++;
        }
        divisor /= 10;
    }
    if (start == dec)
    {
        *dec = '0';
        dec++;
    }
    *dec = '\0';
}
