/* This file is part of the GLEG engine (GPL v2 or later), see LICENSE.html */

#ifndef TERMINAL_H
#define TERMINAL_H

#include <common/types.h>

typedef struct tty_s
{
    void (*write)(struct tty_s);

};

#endif // TERMINAL_H
