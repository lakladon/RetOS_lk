make:
	
	nasm -f elf32 kernel/boot.asm -o build/boot.o
	gcc -m32 -ffreestanding -c kernel/kernel.c -o build/kernel.o
	gcc -m32 -ffreestanding -c kernel/printf.c -o build/printf.o
	ld -m elf_i386 -T kernel/linker.ld -o build/kernel.bin \
		build/boot.o build/kernel.o build/printf.o

iso: make
	mkdir -p iso/boot/grub
	cp build/kernel.bin iso/boot/
	cp boot/grub/grub.cfg iso/boot/grub/
	grub-mkrescue -o build/retos.iso iso/

clean:
	rm -rf build/*
	rm -rf iso/boot/kernel.bin
