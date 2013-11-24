/* This file is part of the GLEG engine (GPL v2 or later), see LICENSE.html */

#ifndef STRING_H
#define STRING_H

#include "common/types.h"

void* memcpy(void *dst, void *src, size_t n);
void* memset(void *dst, char val, size_t n);
void* memsetw(void *dst, u16int val, size_t n);

#endif // STRING_H
