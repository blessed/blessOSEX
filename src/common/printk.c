/* This file is part of the blessOS OS (GPL v2 or later), see LICENSE.html */

#include <common/types.h>
#include <common/printk.h>
#include <console/console.h>

static void parse_hex(char *buf, int num)
{
    int i = 7;
    while (i-- >= 0)
    {
        *buf++ = "0123456789abcdef"[(num >> (i * 4)) & 0x0f];
    }
}

static void parse_num(char *buf, int num, int base)
{
    u32int n = num / base;
    int r = num % base;
    if (r < 0)
    {
        r += base;
        --n;
    }

    if (num >= base)
        parse_num(buf, n, base);

    *buf++ = "0123456789"[r];
}

int printk_get_level(const char *buffer)
{
    if (buffer[0] == KERN_SOH_ASCII && buffer[1])
    {
        switch (buffer[1])
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case 'd':
            return buffer[1];
        }
    }

    return 0;
}

static inline const char *printk_skip_level(const char *buf)
{
    if (printk_get_level(buf))
        return buf + 2;

    return buf;
}

int vsprintf(char *buf, const char *fmt, va_list args)
{
    int i;
    int index;
    char *s;

    index = 0;

    for (i = 0; fmt[i] != '\0'; ++i)
    {
        if ((fmt[i] != '%') && (fmt[i] != '\\'))
        {
            buf[index++] = fmt[i];
            continue;
        }
        else if (fmt[i] == '%')
        {
            switch(fmt[++i])
            {
            case 's':
                s = (char *)va_arg(args, char *);
                while (*s)
                {
                    buf[index++] = *s++;
                }
                break;

            case 'c':
                buf[index++] = (char)va_arg(fmt, char);
                break;

            case 'p':
            case 'x':
                parse_hex(buf, (u32int)va_arg(args, u32int));
                break;

            case 'd':
                parse_num(buf, (u32int)va_arg(args, u32int), 10);
                break;

            case '%':
                buf[index++] = '%';
                break;

            default:
                buf[index++] = fmt[i];
                break;
            }

            continue;
        }

        switch(fmt[++i])
        {
        case 'a':
            buf[index++] = '\a'; break;
        case 'b':
            buf[index++] = '\b'; break;
        case 't':
            buf[index++] = '\t'; break;
        case 'n':
            buf[index++] = '\n'; break;
        case 'r':
            buf[index++] = '\r'; break;
        case '\\':
            buf[index++] = '\\'; break;
        }
    }

    buf[index] = '\0';
    va_end(args);

    return index;
}

int printk(const char *fmt, ...)
{
    int len;
    va_list args;
    char buf[1024];
    char *text;

    CONSOLE_COLOR con_bg = BLACK;
    CONSOLE_COLOR con_fg = WHITE;

    va_start(args, fmt);
    len = vsprintf(buf, fmt, args);
    va_end(args);

    text = buf;

    int kern_level = printk_get_level(buf);

    if (kern_level)
    {
        const char *end_of_header = printk_skip_level(buf);

        len -= end_of_header - buf;
        text = (char *)end_of_header;

        con_bg = RED;
        con_fg = YELLOW;
    }

    int i;
    for (i = 0; i < len; ++i)
    {
        print_c(text[i], con_fg, con_bg);
    }

    return len;
}
