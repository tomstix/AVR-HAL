#pragma once

#include <stdint.h>

typedef enum {
    ADC_PRESCALER_2 = 0,
    ADC_PRESCALER_4 = 2,
    ADC_PRESCALER_16 = 4,
    ADC_PRESCALER_32 = 5,
    ADC_PRESCALER_64 = 6,
    ADC_PRESCALER_128 = 7
} adc_prescaler_t;

typedef enum {
    ADC_VREF_AREF = 0,
    ADC_VREF_AVCC = 64,
    ADC_VREF_MISC1 = 128,
    ADC_VREF_MISC2 = 192
} adc_vref_t;

typedef enum {
    A0 = 0,
    A1 = 1,
    A2 = 2,
    A3 = 3,
    A4 = 4,
    A5 = 5,
    A6 = 6,
    A7 = 7
} adc_pin_t;

uint16_t adc_read(adc_prescaler_t prescaler, adc_vref_t vref, adc_pin_t pin);
void adc_start(adc_prescaler_t prescaler, adc_vref_t vref);
void adc_stop();
