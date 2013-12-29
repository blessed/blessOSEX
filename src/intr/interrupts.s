/* This file is part of the blessOS OS (GPL v2 or later), see LICENSE.html */

.extern isr_handler
.globl idt_flush, isr_stub

.macro isrnoerror nr
.globl isr\nr
isr\nr:
	cli
	push $0
	push $\nr
	jmp isr_stub
.endm

.macro isrerror nr
.globl isr\nr
isr\nr:
	cli
	push $\nr
	jmp isr_stub
.endm

idt_flush:
	movl 4(%esp),%eax
	lidt (%eax)
	ret

isr_stub:
	pushal

	movw %ds, %ax
	pushl %eax

	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs

	call isr_handler

	popl %eax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs

	popal
	addl $8, %esp
	sti
	iret

isrnoerror	0x00
isrnoerror	0x01
isrnoerror	0x02
isrnoerror	0x03
isrnoerror	0x04
isrnoerror	0x05
isrnoerror	0x06
isrnoerror	0x07
isrerror	0x08
isrnoerror	0x09
isrerror	0x0a
isrerror	0x0b
isrerror	0x0c
isrerror	0x0d
isrerror	0x0e
isrnoerror	0x0f
isrerror	0x10
isrnoerror	0x11
isrnoerror	0x12
isrnoerror	0x13
isrnoerror	0x14
isrnoerror	0x15
isrnoerror	0x16
isrnoerror	0x17
isrnoerror	0x18
isrnoerror	0x19
isrnoerror	0x1a
isrnoerror	0x1b
isrnoerror	0x1c
isrnoerror	0x1d
isrnoerror	0x1e
isrnoerror	0x1f
isrnoerror	0x20
isrnoerror	0x21
isrnoerror	0x22
isrnoerror	0x23
isrnoerror	0x24
isrnoerror	0x25
isrnoerror	0x26
isrnoerror	0x27
isrnoerror	0x28
isrnoerror	0x29
isrnoerror	0x2a
isrnoerror	0x2b
isrnoerror	0x2c
isrnoerror	0x2d
isrnoerror	0x2e
isrnoerror	0x2f
