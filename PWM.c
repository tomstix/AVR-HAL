#include "PWM.h"

#include <avr/io.h>

void PWM_Init(const PWM_Pin pin)
{
    // Set the PWM pin as output
    switch (pin)
    {
    case PWM_PIN_3:
        DDRD |= (1 << DDD3);
        break;
    case PWM_PIN_5:
        DDRD |= (1 << DDD5);
        break;
    case PWM_PIN_6:
        DDRD |= (1 << DDD6);
        break;
    case PWM_PIN_9:
        DDRB |= (1 << DDB1);
        break;
    case PWM_PIN_10:
        DDRB |= (1 << DDB2);
        break;
    case PWM_PIN_11:
        DDRB |= (1 << DDB3);
        break;
    }

    if (pin == PWM_PIN_5 || pin == PWM_PIN_6)
    {
        // Set timer 0 to fast PWM mode
        TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
        TCCR0B = _BV(CS00);
    }
    else if (pin == PWM_PIN_9 || pin == PWM_PIN_10)
    {
        // Set timer 1 to fast PWM mode
        TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11);
        TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10);
    }
    else if (pin == PWM_PIN_3 || pin == PWM_PIN_11)
    {
        // Set timer 2 to fast PWM mode
        TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
        TCCR2B = _BV(CS22);
    }
}

void PWM_SetDutyCycle(const PWM_Pin pin, const uint8_t duty_cycle)
{
    switch (pin)
    {
    case PWM_PIN_3:
        OCR2B = duty_cycle;
        break;
    case PWM_PIN_5:
        OCR0B = duty_cycle;
        break;
    case PWM_PIN_6:
        OCR0A = duty_cycle;
        break;
    case PWM_PIN_9:
        OCR1A = duty_cycle;
        break;
    case PWM_PIN_10:
        OCR1B = duty_cycle;
        break;
    case PWM_PIN_11:
        OCR2A = duty_cycle;
        break;
    }
}