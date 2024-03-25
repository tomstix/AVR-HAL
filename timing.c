#include "timing.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/atomic.h>

static volatile uint32_t timer1_millis;

// Timer1 overflow interrupt
ISR(TIMER1_COMPA_vect) { timer1_millis++; }

// Initialize timer1 for the millis() function
// Remember to enable global interrupts after calling this function
void init_millis() {
  unsigned long ctc_match_overflow;

  ctc_match_overflow =
      ((F_CPU / 1000) / 64);  // when timer1 is this value, 1ms has passed

  // (Set timer to clear when matching ctc_match_overflow) | (Set clock divisor
  // to 64)
  TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);

  // high byte first, then low byte
  OCR1AH = ((uint8_t)ctc_match_overflow >> 8);
  OCR1AL = (uint8_t)ctc_match_overflow;

  // Enable the compare match interrupt
  TIMSK1 |= (1 << OCIE1A);
}

// Returns the number of milliseconds since the timer was initialized
uint32_t millis() {
  uint32_t millis_return;

  // Ensure this cannot be disrupted
  ATOMIC_BLOCK(ATOMIC_FORCEON) { millis_return = timer1_millis; }
  return millis_return;
}