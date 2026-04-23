#pragma once

#if defined(__GNUC__) || defined(__clang__)
    #define __furred_clz(x) (x == 0 ? 32 : __builtin_clz(x))
#elif defined(_MSC_VER)
    #include <intrin.h>
    int __furred_clz(unsigned int x) {
        if (x == 0) return 32;

        unsigned int idx;
        _BitScanReverse(&idx, x);
        return 31 - idx;
    }
#else
    int __furred_clz(unsigned int x) {
        if (x == 0) return 32;

        unsigned int cnt = 0;
        for (int i = 31; i >= 0; i--) {
            if ((x >> i) & 1) break;
            cnt++;
        }
        return cnt;
    }
#endif

unsigned int furred_math_next_pow2(unsigned int x) {
    if (x < 2) return 2;
    return ((unsigned int)1 << 31) >> (__furred_clz(x) - 1);
}