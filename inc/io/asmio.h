/* This file is part of the GLEG engine (GPL v2 or later), see LICENSE.html */

#ifndef ASMIO_H
#define ASMIO_H

#include "common/types.h"

void outb(u8int val, u16int port);
u8int inb(u16int port);
void outw(u16int val, u16int port);
u16int inw(u16int port);

#endif // ASMIO_H
