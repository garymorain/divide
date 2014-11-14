/* Tests for divide.c */

#include "divide.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char **argv) {
  bool test_fail = false;
  for (uint32_t m1 = 1; m1 < (1 << 9); m1++) {
    for (uint32_t m2 = m1 + 1; m2 < (1 << 9); m2++) {
      for (uint32_t m3 = 1; m3 < m2; m3++) {
        uint32_t dividend = m1 * m2 + m3;
        uint32_t divisor = m2;
        uint32_t expected_quotient = m1;
        uint32_t expected_remainder = m3;
        uint32_t quotient = 0;
        uint32_t remainder = 0;
        divide(dividend, divisor, &quotient, &remainder);
        if ((quotient != expected_quotient) ||
            (remainder != expected_remainder)) {
          test_fail = true;
          printf("%u/%u.  Want %u, %u.  Got %u, %u\n",
                 dividend, divisor, expected_quotient,
                 expected_remainder,
                 quotient, remainder);
        }
      }
    }
  }
  return (int)test_fail;
}
