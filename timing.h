#pragma once

#include <stdint.h>

volatile uint32_t timer1_millis;

void init_millis();

uint32_t millis();