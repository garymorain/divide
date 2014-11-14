#include "divide.h"

void divide(uint32_t dividend, uint32_t divisor,
            uint32_t *quotient, uint32_t *remainder) {
  const uint32_t msb = 1 << 31;
  int steps = 1;

  if (divisor == 0) {
    return;
  }

  // Shift divisor until the msb is a 1.
  while ((divisor & msb) == 0) {
    divisor <<= 1;
    steps++;
  }

  uint32_t q = 0;
  uint32_t r = dividend;
  for (int i = 0; i < steps; i++) {
    q <<= 1;
    if (r >= divisor) {
      q |= 1;
      r -= divisor;
    }
    divisor >>= 1;
  }
  *quotient = q;
  *remainder = r;
}
