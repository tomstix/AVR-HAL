#include "delay.h"

#include <stddef.h>

// This loop delays for 4 cycles
// We can at most delay for 65535 * 4 / F_CPU seconds
// For a 16MHz clock, this is 65535 * 4 / 16000000 = 16.384 ms
// One cycle at 16MHz is 1 / 16000000 = 0.0625 us
inline void delay_loop(uint16_t __count) {
  __asm__ volatile(
      "1: sbiw %0,1\n\t"
      "brne 1b"
      : "=w"(__count)
      : "0"(__count));
}

// dont't use this function with us > 16384
void delay_us(uint16_t us) {
  uint16_t cycles = (uint16_t)(F_CPU / (us * 4));
  delay_loop(cycles);
}

void delay_ms(unsigned int ms) {
  for (size_t i = 0; i < ms; i++) {
    delay_us(1000);
  }
}

void delay_s(unsigned int s) {
  for (size_t i = 0; i < s; i++) {
    delay_ms(1000);
  }
}
