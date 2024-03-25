#include "adc.h"

#include <avr/interrupt.h>
#include <avr/io.h>

uint16_t adc_read(adc_prescaler_t prescaler, adc_vref_t vref, adc_pin_t pin) {
  ADMUX = (uint8_t)vref | (uint8_t)pin;

  ADCSRA = _BV(ADEN) | _BV(ADSC) | (uint8_t)prescaler;
  while (!(ADCSRA & _BV(ADIF)))
    ;

  return (ADCL | (ADCH << 8));
}

void adc_start(adc_prescaler_t prescaler, adc_vref_t vref) {
  ADMUX = (uint8_t)vref;
  ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADIE) | (uint8_t)prescaler;
}

void adc_stop() { ADCSRA = 0; }