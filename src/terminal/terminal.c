/* This file is part of the blessOS OS (GPL v2 or later), see LICENSE.html */

#include <common/types.h>
#include <terminal/terminal.h>

tty_t tty_table[TERMINAL_COUNT] = {
    { NULL,
      { 0, 0, { 0, } },
      { 0, 0, { 0. } }
    }
};

void init_tty(void)
{
    int i = 0;
    for (i = 0; i < 1; ++i)
    {
        tty_table[i].write = NULL;
        cb_init(&tty_table[i].read_buf);
        cb_init(&tty_table[i].write_buf);
    }
}

void con_write(tty_t *tty)
{
    if (tty->write)
        tty->write(tty);
}
