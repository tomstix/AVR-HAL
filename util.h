#pragma once

#include <stddef.h>
#include <stdint.h>

#define PI 3.14159265359

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define ABS(X) (((X) < 0) ? -(X) : (X))
#define CLAMP(X, MIN, MAX) (((X) < (MIN)) ? (MIN) : ((X) > (MAX)) ? (MAX) : (X))

void byte_to_hex(uint8_t byte, char *hex);

void any_to_hex_str(const void *data, size_t size, char *hex);

void char_to_hex_str(char value, char *hex);

void int_to_hex_str(int value, char *hex);

void long_to_hex_str(long value, char *hex);

void int_to_dec_str(int32_t value, char *dec);

void uint_to_dec_str(uint32_t value, char *dec);

void float_to_dec_str(const float value, char *dec, const int precision);
