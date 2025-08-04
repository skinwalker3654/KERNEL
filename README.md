# Simple Multiboot2 Kernel with Printk

A minimal **32-bit Multiboot2-compatible kernel** 
written in C and NASM, featuring a basic `clear_screen`
and `printk` function for text output.

## 📂 Project Structure

```text
KERNEL/
├── boot/
│ └── boot.asm # Multiboot2 bootloader (ASM)
│
├── kernel/
│ └── kernel.c # Kernel main code (printk, clear_screen)
│
├── iso/
│ └── grub/
│   └── grub.cfg # GRUB configuration file
│
├── linker.ld # connects object files
├── Makefile # Build automation
└── README.md # This file
```

## 🛠️ Build & Run

### Requirements
- **GCC** (32-bit target support)
- **NASM** (for assembly)
- **GNU Make**
- **GRUB** (for ISO generation)
- **QEMU** (for emulation)

### CommandsRun in QEMU
1. **Build the kernel and create ISO**
   ```sh
   make 
   ```
2. **Run in QEMU**
    ```sh
    make run
    ```
3. **Clean build files**
    ```sh
    make clean
    ```
