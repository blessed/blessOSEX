#include "common/types.h"
#include "console/console.h"
#include <common/circular_buffer.h>
#include <terminal/terminal.h>
#include <common/printk.h>

unsigned int user_stack[4096 >> 2];
struct {
    u32int *a;
    u16int b;
} stack_start = { &user_stack[4096 >> 2], 0x10 };


void main(void)
{
    console_init();

    circ_buf_t buf;
    cb_init(&buf);

    cb_push(&buf, 0xdeadbeef);
    u32int tmp;
    tmp = cb_pop(&buf);

    init_tty();

    printk(KERN_DEBUG "Dupa\n");
    printk("Druga dupa\n");

    __asm__("hlt");
}
