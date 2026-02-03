make:
	
	nasm -f elf32 kernel/boot.asm -o build/boot.o
	gcc -m32 -ffreestanding -c kernel/kernel.c -o build/kernel.o
	gcc -m32 -ffreestanding -c kernel/printf.c -o build/printf.o
	ld -m elf_i386 -T kernel/linker.ld -o build/kernel.bin \
		build/boot.o build/kernel.o build/printf.o

clean:
	rm -rf build/*
