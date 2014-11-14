/* Tests for divide.c */

#include "divide.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char **argv) {
  bool test_fail = false;
  for (uint32_t dividend = 1024; dividend < 0xfff00000; dividend = dividend + 1024) {
    for (uint32_t divisor = 1; divisor < 1025; divisor = divisor * 2) {
      uint32_t expected_quotient = dividend / divisor;
      uint32_t expected_remainder = dividend % divisor;
      uint32_t quotient = 0;
      uint32_t remainder = 0;
      divide(dividend, divisor, &quotient, &remainder);
      if ((quotient != expected_quotient) || (remainder != expected_remainder)) {
        test_fail = true;
        printf("%u/%u.  Want %u, %u.  Got %u, %u\n",
               dividend, divisor, expected_quotient, expected_remainder,
               quotient, remainder);
      }
    }
  }
    return (int)test_fail;
}
