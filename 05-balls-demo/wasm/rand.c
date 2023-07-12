#include <stdint.h>

#define CMWC_CYCLE 4096
#define CMWC_C_MAX 809430660

static uint32_t Q[CMWC_CYCLE];
static uint32_t c = 362436; // Carry, must be limited to [0, CMWC_C_MAX]
static uint32_t index = CMWC_CYCLE - 1;

void init_rand(uint32_t x) {
    // A simple linear congruential generator for seeding
    uint32_t i;
    uint32_t seed = x;
    for (i = 0; i < CMWC_CYCLE; i++) {
        seed = (seed * 1664525) + 1013904223;
        Q[i] = seed;
    }
    // Initializing carry
    c = (c * 1664525) + 1013904223;
}

uint32_t rand_cmwc(void) {
    uint64_t t, a = 18782LL;
    uint32_t x, r = 0xfffffffe;
    index = (index + 1) & (CMWC_CYCLE - 1);
    t = a * Q[index] + c;
    c = (uint32_t)(t >> 32);
    x = (uint32_t)t + c;
    if (x < c) {
        x++;
        c++;
    }
    return (Q[index] = r - x);
}

float rand_float(void) {
    return ((float)rand_cmwc() / (float)UINT32_MAX);
}
