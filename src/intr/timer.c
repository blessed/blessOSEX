/* This file is part of the blessOS OS (GPL v2 or later), see LICENSE.html */

#include <io/asmio.h>
#include <intr/intr.h>
#include <intr/timer.h>
#include <common/printk.h>

u32int tick = 0;

static void timer_handler(registers_t regs)
{
    tick++;
    printk("Tick: %d\n", tick);
}

void init_timer(u32int frequency)
{
    register_intr_handler(0x20, timer_handler);

    u32int divisor = 1193180 / frequency;

    outb(0x36, 0x43);

    u8int l = (u8int)(divisor & 0xff);
    u8int h = (u8int)((divisor >> 8) & 0xff);

    outb(l, 0x40);
    outb(h, 0x40);

    outb(inb(INTR_PIC_1_DATA) & ~0x01, INTR_PIC_1_DATA);
}
