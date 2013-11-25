/* This file is part of the blessOS OS (GPL v2 or later), see LICENSE.html */

#ifndef TERMINAL_H
#define TERMINAL_H

#include <common/types.h>
#include <common/circular_buffer.h>

#define TERMINAL_COUNT  2

typedef struct tty_s
{
    void (*write)(struct tty_s *);
    circ_buf_t write_buf;
    circ_buf_t read_buf;
} tty_t;

extern tty_t tty_table[];

void init_tty(void);

#endif // TERMINAL_H
