/* This file is part of the blessOS OS (GPL v2 or later), see LICENSE.html */

#ifndef INTR_H
#define INTR_H

#include <common/types.h>

#define INTR_PIC_ICW1       0x11

#define INTR_PIC_1_CTRL     0x20
#define INTR_PIC_2_CTRL     0xa0

#define INTR_PIC_1_DATA     0x21
#define INTR_PIC_2_DATA     0xa1

#define INTR_PIC_IRQ0       0x20
#define INTR_PIC_IRQ8       0x28

#define INTR_FLAGS_INTR_GATE    0x8e
#define INTR_FLAGS_TRAP_GATE    0x8f

#define INTR_HW_INTERRUPTS_COUNT    32
#define INTR_INTERRUPTS_COUNT       256
#define INTR_USR_INTERRUPTS_COUNT   \
    (INTR_INTERRUPTS_COUNT - INTR_HW_INTERRUPTS_COUNT)

struct registers_s;

typedef void (*irq_handler)(struct registers_s r);

struct idt_entry_s
{
    u16int base_low;
    u16int selector;
    u8int always_zero;
    u8int flags;
    u16int base_high;
} __attribute__((packed));
typedef struct idt_entry_s idt_entry_t;

struct idt_s
{
    u16int limit;
    u32int base;
} __attribute__((packed));
typedef struct idt_s idt_t;

typedef struct registers_s
{
    u32int ds;
    u32int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    u32int int_no, err_code;
    u32int eip, cs, eflags, useresp, ss;
} registers_t;

void init_idt();
inline void cli();
inline void sti();
int register_intr_handler(u8int irq, irq_handler handler);

void init_pic();

extern void isr0x00();
extern void isr0x01();
extern void isr0x02();
extern void isr0x03();
extern void isr0x04();
extern void isr0x05();
extern void isr0x06();
extern void isr0x07();
extern void isr0x08();
extern void isr0x09();
extern void isr0x0a();
extern void isr0x0b();
extern void isr0x0c();
extern void isr0x0d();
extern void isr0x0e();
extern void isr0x0f();
extern void isr0x10();
extern void isr0x11();
extern void isr0x12();
extern void isr0x13();
extern void isr0x14();
extern void isr0x15();
extern void isr0x16();
extern void isr0x17();
extern void isr0x18();
extern void isr0x19();
extern void isr0x1a();
extern void isr0x1b();
extern void isr0x1c();
extern void isr0x1d();
extern void isr0x1e();
extern void isr0x1f();
extern void isr0x20();
extern void isr0x21();
extern void isr0x22();
extern void isr0x23();
extern void isr0x24();
extern void isr0x25();
extern void isr0x26();
extern void isr0x27();
extern void isr0x28();
extern void isr0x29();

#endif // INTR_H
