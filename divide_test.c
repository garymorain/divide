/* Tests for divide.c */

#include "divide.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

static bool test_fail = false;

void test_divide(uint32_t dividend, uint32_t divisor,
                 uint32_t expected_quotient, uint32_t expected_remainder) {
    uint32_t quotient, remainder;
    divide(dividend, divisor, &quotient, &remainder);
    if ((quotient != expected_quotient) || (remainder != expected_remainder)) {
        test_fail = true;
        printf("%u/%u.  Want %u, %u.  Got %u, %u\n",
               dividend, divisor, expected_quotient, expected_remainder,
               quotient, remainder);
    }
}

int main(int argc, char **argv) {
    test_divide(12, 3, 4, 0);
    test_divide(13, 3, 4, 1);
    for (int i = 0; i < 122; i++) {
        test_divide(56088 + i, 123, 456, i);
    }
    test_divide(9999, 9999, 1, 0);
    test_divide(9999, 0, 0xffffffff, 9999);
    test_divide(0x80000000, 0x10000000, 8, 0);
    test_divide(0xffffffff, 0x10000000, 0xf, 0x0fffffff);
    return (int)test_fail;
}
