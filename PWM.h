#pragma once

#include <stdint.h>

typedef enum {
  PWM_PIN_3 = 3,
  PWM_PIN_5 = 5,
  PWM_PIN_6 = 6,
  PWM_PIN_9 = 9,
  PWM_PIN_10 = 10,
  PWM_PIN_11 = 11
} PWM_Pin;

void pwm_init(PWM_Pin pin);

void pwm_set_duty(const PWM_Pin pin, const uint8_t duty_cycle);