#include "common/types.h"
#include "console/console.h"
#include <common/circular_buffer.h>
#include <terminal/terminal.h>
#include <common/printk.h>
#include <intr/intr.h>
#include <intr/timer.h>

unsigned int user_stack[4096 >> 2];
struct {
    u32int *a;
    u16int b;
} stack_start = { &user_stack[4096 >> 2], 0x10 };


void main(void)
{
    console_init();
    init_tty();
    cli();
    init_idt();
    init_timer(50);

    while (1)
    {
        asm ("nop");
    }

    __asm__("hlt");
}
