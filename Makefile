INCLUDE_DIR = $(KERNEL_SRC)/inc
OBJ_DIR = $(KERNEL_SRC)/obj
DISASM_DIR = $(KERNEL_SRC)/disasm

AS = as
ASFLAGS = -32
CC = gcc
CFLAGS = -Wall -Wextra -Wno-main -m32 -nostdinc -nostdlib -fno-builtin -I$(INCLUDE_DIR) -g
#LDFLAGS = --oformat binary -mi386linux -Tscript.ld
LDFLAGS = -Tscript.ld
SOURCES=$(shell find . -iname '*.cpp')

.PHONY: all clean bochs qemu qemu_debug info

KERNEL_SRC = /home/blessed/Programowanie/blessOS/ex

%.o : %.s
	@$(AS) $(ASFLAGS) $< -o $@

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

%.disasm : %.o
	@objdump -DSr $< > $@

all:main image disasm
	@echo "Done. System successfully built."

sources := $(shell find $(KERNEL_SRC) -regex '.*\.\(c\|s\)')
SRCDIRS = $(shell find $(KERNEL_SRC)/src -type d | sed 's/src/./g')
#objects := $(addprefix $(OBJ_DIR)/,$(sources:%.c=%.o))
#objects := $(patsubst $(KERNEL_SRC)/src/%.c,%.o,$(sources))
objects := $(patsubst %.c,%.o,$(sources))
objects := $(patsubst %.s,%.o,$(objects))
disasms := $(objects:%.o=%.disasm)

info:
	$(info $(objects))

main: $(objects)
	@echo -n "Building the system... "
	@$(LD) $(LDFLAGS) $^ -o $@ -M > kernel.map
	objcopy -O binary $@ $@.bin

image:
	@echo "Writing the image to floppy... "
	dd of=floppy.img if=main.bin bs=1 seek=512

disasm: $(DISASM_DIR) $(disasms)
	@echo "Disassembling system object files"

qemu:
	qemu -fda floppy.img -hda disk.img -boot a -m 8

clean:
	@echo "Cleaning object files... "
	-@rm -f $(objects)

$(OBJ_DIR):
	mkdir -p $@

