#pragma once

#include <limits.h>

typedef unsigned long long FE_size_t;

int __furred_clz(unsigned int x);
int __furred_clzl(unsigned long x);
int __furred_clzll(unsigned long long x);

FE_size_t furred_math_next_pow2(FE_size_t x);