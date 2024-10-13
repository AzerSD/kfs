NAME = ReverseKernel
ASM = boot.s
BIN = bin/
SRC = kernel.c
LINKER = linker.ld
CC = gcc
CFLAGS = -Wall -Wextra -Woverflow -m32 -ffreestanding -fno-builtin -nostdlib -nodefaultlibs


all: build

linux:
	sudo apt install xorriso
	sudo apt install nasm
	sudo apt install qemu qemu-system-i386
	sudo apt install mtools

build:
	@mkdir -p $(BIN)
	nasm -f elf32 $(ASM) -o $(BIN)boot.o
	$(CC) $(CFLAGS) -c $(SRC) -o $(BIN)kernel.o -ggdb
	ld -m elf_i386 -T$(LINKER) -o $(BIN)kernel.bin $(BIN)boot.o $(BIN)kernel.o
	@if grub-file --is-x86-multiboot $(BIN)kernel.bin; then \
        echo multiboot confirmed; \
    else \
        echo the file is not multiboot; \
    fi

kernel: build
	@qemu-system-i386 -kernel ${KERNEL_OUT}

image: build
	mkdir -p iso/boot/grub
	cp $(BIN)kernel.bin iso/boot/
	cp grub.cfg iso/boot/grub/
	grub-mkrescue -o $(NAME).iso iso

qemu: image
	qemu-system-i386 -cdrom $(NAME).iso -d int -no-reboot -no-shutdown

qemu-gdb: image
	qemu-system-i386 -cdrom $(NAME).iso -s -S

clean:
	rm -rf $(BIN)
	rm -rf iso
	rm -f $(NAME).iso

docker_build:
	docker build -t kfs .

docker_run:
	docker run kfs

docker_exec:
	docker exec -it ADD_PLACEHOLDER_HERE /bin/bash