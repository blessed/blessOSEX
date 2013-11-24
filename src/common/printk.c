/* This file is part of the GLEG engine (GPL v2 or later), see LICENSE.html */

#include <common/types.h>
#include <common/printk.h>

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

    va_start(args, fmt);
    len = vsprintf(buf, fmt, args);
    va_end(args);



    return len;
}
