/* This file is part of the blessOS OS (GPL v2 or later), see LICENSE.html */

#include <common/types.h>
#include <io/asmio.h>
#include <common/string.h>
#include <common/circular_buffer.h>
#include <console/console.h>
#include <terminal/terminal.h>

static int csr_x, csr_y;

static void scroll_down()
{
    int i;
    u16int *vga_mem = (u16int *)VRAM_START;
    u16int blank = 0x20 | (((0 << 4) | (15 & 0xff)) << 8);

    memcpy(vga_mem, vga_mem + CONSOLE_WIDTH,
           (CONSOLE_HEIGHT - 1) * CONSOLE_WIDTH * CONSOLE_CHAR_SIZE);

    for (i = 0; i < CONSOLE_WIDTH; ++i)
    {
        vga_mem[CONSOLE_WIDTH * (CONSOLE_HEIGHT - 1) + i] = blank;
    }
}

void set_cursor(int x, int y)
{
    u16int position;
    csr_x = x;
    csr_y = y;

    position = csr_y * CONSOLE_WIDTH + csr_x;

    outb(0x0f, 0x3d4);
    outb((u8int)(position & 0xff), 0x3d5);
    outb(0x0e, 0x3d4);
    outb((u8int)((position >> 8) & 0xff), 0x3d5);
}

void get_cursor(int *x, int *y)
{
    *x = csr_x;
    *y = csr_y;
}

void console_init()
{
    clear_screen();

    set_cursor(0, 0);
}

void clear_screen()
{
    u16int *vga_mem = (u16int *)VRAM_START;
    u16int blankchar = 0x20 | (((0 << 4 ) | (15 & 0xff)) << 8);

    int count = CONSOLE_WIDTH * CONSOLE_HEIGHT;
    for (; count > 0; count--)
        *vga_mem++ = blankchar;
}

void console_write(tty_t *tty)
{
    int len = cb_size(&tty->write_buf);

    while (len--)
    {
        char c = (char)cb_pop(&tty->write_buf);
        print_c(c, WHITE, BLACK);
    }
}

void print_c(char c, CONSOLE_COLOR fg, CONSOLE_COLOR bg)
{
    u8int *dest = (u8int *)(VRAM_START + csr_y * VRAM_LINE + csr_x * CONSOLE_CHAR_SIZE);
    u8int attr = (u8int)(bg << 4 | fg );

    switch (c)
    {
    case '\r':
        csr_x = 0;
        break;
    case '\n':
        for (; csr_x < CONSOLE_WIDTH; ++csr_x)
        {
            *dest++ = BLANK_CHAR;
            *dest++ = attr;
        }
        break;
    case '\t':
        c = csr_x + TAB_WIDTH - (csr_x % TAB_WIDTH);
        c = c < CONSOLE_WIDTH ? c : CONSOLE_WIDTH;
        for (; csr_x < c; ++csr_x)
        {
            *dest++ = (u8int)BLANK_CHAR;
            *dest++ = (u8int)BLANK_ATTR;
        }
        break;
    case '\b':
        if ((!csr_x) && (!csr_y))
            return;

        if (!csr_x)
        {
            csr_x = CONSOLE_WIDTH - 1;
            --csr_y;
        } else
            --csr_x;

        dest[-1] = (u8int)BLANK_ATTR;
        dest[-2] = (u8int)BLANK_CHAR;
        break;
    default:
        *dest++ = c;
        *dest++ = attr;
        ++csr_x;
        break;
    }

    if (csr_x >= CONSOLE_WIDTH)
    {
        csr_x = 0;
        if (csr_y < (CONSOLE_HEIGHT - 1))
            csr_y++;
        else
            scroll_down();
    }

    set_cursor(csr_x, csr_y);
}
