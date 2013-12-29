/* This file is part of the blessOS OS (GPL v2 or later), see LICENSE.html */

#include <io/asmio.h>
#include <common/string.h>
#include <common/errno.h>
#include <common/printk.h>
#include <intr/intr.h>

extern idt_t idt_descr;
extern idt_entry_t idt;

static irq_handler irq_handlers[INTR_INTERRUPTS_COUNT];

extern void idt_flush(idt_t *idt_d);

static void idt_add_gate(u8int num, u32int fun, u16int sel, u8int flags)
{
    idt_entry_t *idt_ptr = &idt;

    idt_ptr[num].base_low = fun & 0xffff;
    idt_ptr[num].base_high = (fun >> 16) & 0xffff;

    idt_ptr[num].selector = sel;
    idt_ptr[num].always_zero = 0;
    idt_ptr[num].flags = flags;
}

void isr_handler(registers_t regs)
{
    if (!irq_handlers[regs.int_no])
    {
        printk(KERN_ERR "Unserviced interrupt %d\n", regs.int_no);
        outb(0x20, 0x20);
        outb(0x20, 0xa0);
        return;
    }

    irq_handlers[regs.int_no](regs);

    outb(0x20, 0x20);
}

void init_pic()
{
    outb(INTR_PIC_ICW1, INTR_PIC_1_CTRL);
    outb(INTR_PIC_ICW1, INTR_PIC_2_CTRL);
    outb(INTR_PIC_IRQ0, INTR_PIC_1_DATA);
    outb(INTR_PIC_IRQ8, INTR_PIC_2_DATA);
    outb(0x04, INTR_PIC_1_DATA);
    outb(0x02, INTR_PIC_2_DATA);
    outb(0x01, INTR_PIC_1_DATA);
    outb(0x01, INTR_PIC_2_DATA);
    outb(0xff, INTR_PIC_1_DATA);
    outb(0xff, INTR_PIC_2_DATA);
}

void cli()
{
    asm volatile("cli");
}

void sti()
{
    asm volatile("sti");
}

int register_intr_handler(u8int irq, irq_handler handler)
{
    if (!handler)
        return -EINVAL;

    irq_handlers[irq] = handler;

    return 0;
}

void init_idt()
{
    idt_t *idt_table = &idt_descr;

    idt_table->limit = sizeof(idt_entry_t) * 256 - 1;
    idt_table->base = (u32int)&idt;

    memset(&idt, 0, sizeof(idt_entry_t) * 256);

    idt_add_gate(0, (u32int)isr0x00, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(1, (u32int)isr0x01, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(2, (u32int)isr0x02, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(3, (u32int)isr0x03, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(4, (u32int)isr0x04, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(5, (u32int)isr0x05, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(6, (u32int)isr0x06, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(7, (u32int)isr0x07, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(8, (u32int)isr0x08, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(9, (u32int)isr0x09, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(10, (u32int)isr0x0a, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(11, (u32int)isr0x0b, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(12, (u32int)isr0x0c, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(13, (u32int)isr0x0d, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(14, (u32int)isr0x0e, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(15, (u32int)isr0x0f, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(16, (u32int)isr0x10, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(17, (u32int)isr0x11, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(18, (u32int)isr0x12, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(19, (u32int)isr0x13, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(20, (u32int)isr0x14, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(21, (u32int)isr0x15, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(22, (u32int)isr0x16, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(23, (u32int)isr0x17, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(24, (u32int)isr0x18, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(25, (u32int)isr0x19, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(26, (u32int)isr0x1a, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(27, (u32int)isr0x1b, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(28, (u32int)isr0x1c, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(29, (u32int)isr0x1d, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(30, (u32int)isr0x1e, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(31, (u32int)isr0x1f, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(32, (u32int)isr0x20, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(33, (u32int)isr0x21, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(34, (u32int)isr0x22, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(35, (u32int)isr0x23, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(36, (u32int)isr0x24, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(37, (u32int)isr0x25, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(38, (u32int)isr0x26, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(39, (u32int)isr0x27, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(40, (u32int)isr0x28, 0x08, INTR_FLAGS_INTR_GATE);
    idt_add_gate(41, (u32int)isr0x29, 0x08, INTR_FLAGS_INTR_GATE);

    init_pic();

    idt_flush(idt_table);

    sti();
    outb(inb(INTR_PIC_1_DATA) & 0xfd, INTR_PIC_1_DATA);
}
