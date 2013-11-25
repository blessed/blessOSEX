/* This file is part of the blessOS OS (GPL v2 or later), see LICENSE.html */

#ifndef CONSOLE_H
#define CONSOLE_H

#define CONSOLE_WIDTH           80
#define CONSOLE_HEIGHT          25
#define CONSOLE_CHAR_SIZE       2
#define CONSOLE_SIZE            (CONSOLE_WIDTH * CONSOLE_HEIGHT * CONSOLE_CHAR_SIZE)

#define VRAM_START              0xb8000
#define VRAM_END                (VRAM_START + CONSOLE_SIZE)
#define VRAM_LINE               (CONSOLE_WIDTH * 2)

#define BLANK_CHAR              0x20
#define BLANK_ATTR              0x07

#define TAB_WIDTH               4

typedef enum CONSOLE_COLOR
{
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, WHITE,
    GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
    LIGHT_RED, LIGHT_MAGENTA, YELLOW, BRIGHT_WHITE
} CONSOLE_COLOR;

void console_init();
void clear_screen();

void set_cursor(int x, int y);
void get_cursor(int *x, int *y);

/**
  Prints a character on the console
*/
void print_c(char c, CONSOLE_COLOR fg, CONSOLE_COLOR bg);

#endif // CONSOLE_H
