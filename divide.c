#include "divide.h"

void divide(uint32_t dividend, uint32_t divisor,
            uint32_t *quotient, uint32_t *remainder) {
    const uint32_t msb = 1 << 31;
    uint32_t q = 0;
    uint32_t r = 0;

    for (int i = 0; i < 32; i++) {
        r = (r << 1) | (dividend >> 31);
        dividend <<= 1;
        q <<= 1;
        uint32_t diff = r - divisor;
        if ((diff & msb) == 0) {
            q |= 1;
            r = diff;
        }
    }

    *quotient = q;
    *remainder = r;
}
