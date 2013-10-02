INCLUDE_DIR = $(KERNEL_SRC)/inc
BUILD_DIR = $(KERNEL_SRC)/build
DISASM_DIR = $(KERNEL_SRC)/disasm

AS = as
ASFLAGS = -32
CC = gcc
CFLAGS = -Wall -Wextra -Wno-main -m32 -nostdinc -nostdlib -fno-builtin -I$(INCLUDE_DIR) -g
#LDFLAGS = --oformat binary -mi386linux -Tscript.ld
LDFLAGS = -Tscript.ld
SOURCES=$(shell find . -iname '*.cpp')

.PHONY: all clean bochs qemu qemu_debug

KERNEL_SRC = /home/blessed/Programowanie/blessOS/ex

%.o : %.s
	@$(AS) $(ASFLAGS) $< -o $@

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

%.disasm : %.o
	@objdump -DSr $< > $@

all: main image disasm
	@echo "Done. System successfully built."

sources := $(shell find $(KERNEL_SRC) -name '*.c')
objects := $(addprefix $(BUILD_DIR)/,$(sources:%.c=%.o))
disasms := $(objects:%.o=%.disasm)

main: $(BUILD_DIR) $(objects)
	@echo -n "Building the system... "
	$(LD) $(LDFLAGS) $^ -o $@ -M > kernel.map
	objcopy -O binary $@ $@.bin
	@echo "Done"

image:
	@echo -n "Writing the image to floppy... "
	dd of=floppy.img if=main.bin bs=1 seek=512
	@echo "Done"

disasm: $(DISASM_DIR) $(disasms)
	@echo "Disassembling system object files"

clean:
	@echo -n "Cleaning object files... "
	-@rm $(objects)
	@echo "Done"

$(BUILD_DIR):
	mkdir -p $@

$(DISASM_DIR):
	mkdir -p $@

