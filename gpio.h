#pragma once

#include <avr/io.h>
#include <stdbool.h>

typedef struct {
  volatile uint8_t *port;
  volatile uint8_t *ddr;
  volatile uint8_t *pin;
  uint8_t pin_number;
} gpio_t;

typedef enum gpio_direction {
  GPIO_INPUT = 0,
  GPIO_OUTPUT = 1
} gpio_direction_t;

static const gpio_t ARDU_PIN_0 = {&PORTD, &DDRD, &PIND, PIND0};
static const gpio_t ARDU_PIN_1 = {&PORTD, &DDRD, &PIND, PIND1};
static const gpio_t ARDU_PIN_2 = {&PORTD, &DDRD, &PIND, PIND2};
static const gpio_t ARDU_PIN_3 = {&PORTD, &DDRD, &PIND, PIND3};
static const gpio_t ARDU_PIN_4 = {&PORTD, &DDRD, &PIND, PIND4};
static const gpio_t ARDU_PIN_5 = {&PORTD, &DDRD, &PIND, PIND5};
static const gpio_t ARDU_PIN_6 = {&PORTD, &DDRD, &PIND, PIND6};
static const gpio_t ARDU_PIN_7 = {&PORTD, &DDRD, &PIND, PIND7};
static const gpio_t ARDU_PIN_8 = {&PORTB, &DDRB, &PINB, PINB0};
static const gpio_t ARDU_PIN_9 = {&PORTB, &DDRB, &PINB, PINB1};
static const gpio_t ARDU_PIN_10 = {&PORTB, &DDRB, &PINB, PINB2};
static const gpio_t ARDU_PIN_11 = {&PORTB, &DDRB, &PINB, PINB3};
static const gpio_t ARDU_PIN_12 = {&PORTB, &DDRB, &PINB, PINB4};
static const gpio_t ARDU_PIN_13 = {&PORTB, &DDRB, &PINB, PINB5};
static const gpio_t ARDU_PIN_A0 = {&PORTC, &DDRC, &PINC, PINC0};
static const gpio_t ARDU_PIN_A1 = {&PORTC, &DDRC, &PINC, PINC1};
static const gpio_t ARDU_PIN_A2 = {&PORTC, &DDRC, &PINC, PINC2};
static const gpio_t ARDU_PIN_A3 = {&PORTC, &DDRC, &PINC, PINC3};
static const gpio_t ARDU_PIN_A4 = {&PORTC, &DDRC, &PINC, PINC4};
static const gpio_t ARDU_PIN_A5 = {&PORTC, &DDRC, &PINC, PINC5};

void gpio_set_dir(const gpio_t *gpio, const gpio_direction_t dir);

void gpio_enable_pullup(const gpio_t *gpio);

void gpio_write(const gpio_t *gpio, const bool value);

uint8_t gpio_read(const gpio_t *gpio);
