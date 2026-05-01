#include <FurredEngine/math.h>

#if LONG_MAX == 2147483647L
    #define __FE_LongSize 32
#elif LONG_MAX == 9223372036854775807L
    #define __FE_LongSize 64
#else
    #define __FE_LongSize (8 * sizeof(long))
#endif

#if defined(__GNUC__) || defined(__clang__)

int __furred_clz(unsigned int x) {
    if (x == 0) return 32;
    else return __builtin_clz(x);
}
int __furred_clzl(unsigned long x) {
    if (x == 0) return __FE_LongSize;
    else return __builtin_clzl(x);
}
int __furred_clzll(unsigned long long x) {
    if (x == 0) return 64;
    else return __builtin_clzll(x);
}

#elif defined(_MSC_VER)

#include <intrin.h>
int __furred_clz(unsigned int x) {
    if (x == 0) return 32;

    unsigned long idx;
    _BitScanReverse(&idx, x);
    return 31 - idx;
}
int __furred_clzl(unsigned long x) {
    if (x == 0) return __FE_LongSize;

    unsigned long idx;
    #if LONG_MAX > 2147483647L
    _BitScanReverse64(&idx, x);
    #else
    _BitScanReverse(&idx, x);
    #endif
    return (__FE_LongSize - 1) - idx;
}
int __furred_clzll(unsigned long long x) {
    if (x == 0) return 64;

    unsigned long idx;
    _BitScanReverse(&idx, x);
    return 63 - idx;
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
int __furred_clzl(unsigned long x) {
    if (x == 0) return __FE_LongSize;

    unsigned long cnt = 0;
    for (int i = __FE_LongSize - 1; i >= 0; i--) {
        if ((x >> i) & 1) break;
        cnt++;
    }
    return cnt;
}
int __furred_clzll(unsigned long long x) {
    if (x == 0) return 64;

    unsigned long long cnt = 0;
    for (int i = 63; i >= 0; i--) {
        if ((x >> i) & 1) break;
        cnt++;
    }
    return cnt;
}

#endif

FE_size_t furred_math_next_pow2(FE_size_t x) {
    if (x < 2) return 2;
    return ((FE_size_t)1 << 63) >> (__furred_clzll(x) - 1);
}