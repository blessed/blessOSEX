/* This file is part of the blessOS OS (GPL v2 or later), see LICENSE.html */

#include "io/asmio.h"

void outb(u8int val, u16int port)
{
    asm("outb %%al, %%dx" : : "a"(val), "d"(port));
}

void outw(u16int val, u16int port)
{
    asm("outw %%ax, %%dx" : : "a"(val), "d"(port));
}

u8int inb(u16int port)
{
    u8int ret;
    asm("inb %%dx, %%al" : "=a"(ret) : "d"(port));

    return ret;
}

u16int inw(u16int port)
{
    u16int ret;
    asm("inw %%dx, %%ax" : "=a"(ret) : "d"(port));

    return ret;
}
