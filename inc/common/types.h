/* This file is part of the GLEG engine (GPL v2 or later), see LICENSE.html */

#ifndef TYPES_H
#define TYPES_H

#define NULL                ((void *)0)

typedef char*   va_list;

#define  _AUPBND            (sizeof (int) - 1)
#define  _ADNBND            (sizeof (int) - 1)

#define _bnd(X, bnd)        (((sizeof(X)) + (bnd)) & (~(bnd)))
#define va_start(ap, A)     (void)((ap) = (((char *)&(A)) + (_bnd(A,_AUPBND))))
#define va_arg(ap, T)       (*(T *)(((ap) += (_bnd(T, _AUPBND))) - (_bnd(T,_AUPBND))))
#define va_end(ap)          (ap = (va_list)NULL)

typedef int                 size_t;

typedef unsigned int        u32int;
typedef unsigned short      u16int;
typedef unsigned char       u8int;

#endif // TYPES_H
