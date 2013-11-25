/* This file is part of the blessOS OS (GPL v2 or later), see LICENSE.html */

#include "common/string.h"

void* memcpy(void *dst, void *src, size_t n)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dst;

    for (; n > 0; --n)
        *dp++ = *sp++;

    return dst;
}

void *memset(void *dst, char val, size_t n)
{
    char *dp = (char *)dst;

    for (; n > 0; --n)
    {
        *dp++ = val;
    }

    return dst;
}
