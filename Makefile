# COMPILERS
CC = gcc
ASM = nasm
LD = ld

# DIRECTORIES
BOOT_DIR = boot
KERNEL_DIR = kernel
ISO_DIR = iso

# FLAGS
CFLAG = -m32 -ffreestanding -nostdlib -Wall -Wextra -c
ASMFLAG = -f elf32
LDFLAG = -m elf_i386 -T linker.ld

# FILES
SRC = $(KERNEL_DIR)/kernel.c
BOOT = $(BOOT_DIR)/boot.asm
KERNEL_ELF = $(ISO_DIR)/boot/kernel.elf
BOOT_O = $(BOOT_DIR)/boot.o
KERNEL_O = $(KERNEL_DIR)/kernel.o
OBJ = $(BOOT_O) $(KERNEL_O)

# RULES
all: os.iso

$(BOOT_O): $(BOOT)
	@echo "Compiling bootloader..."
	$(ASM) $(ASMFLAG) $< -o $@

$(KERNEL_O): $(SRC)
	@echo "Compiling kernel..."
	$(CC) $(CFLAG) $< -o $@

$(KERNEL_ELF): $(OBJ)
	@echo "Linking kernel..."
	$(LD) $(LDFLAG) $^ -o $@

os.iso: $(KERNEL_ELF)
	@echo "Creating ISO file..."
	grub-mkrescue -o $@ $(ISO_DIR)

run: os.iso
	@echo "Running the OS..."
	qemu-system-x86_64 -cdrom os.iso

clean:
	rm -rf $(OBJ) $(KERNEL_ELF) os.iso

.PHONY: all os run clean
