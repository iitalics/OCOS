target=OCOS.bin
bin: $(target)
all: $(target) boot-check qemu

wd:=$(shell pwd)

# global compiler flags
gASFLAGS =
gCFLAGS = -Wall -O2 -nostdlib -std=c99 -I$(wd)src
gCXXFLAGS = -Wall -O2 -nostdlib -std=c++11 -I$(wd)/src 
export gASFLAGS
export gCFLAGS
export gCXXFLAGS

# linker
linkscript=src/linker.ld
LD=ld -melf_i386
LDFLAGS=


libs = src/boot/libboot.a src/kernel/libkernel.a src/io/libio.a

# libraries
.PHONY: src/boot/libboot.a
src/boot/libboot.a:
	@$(MAKE) libboot.a -C src/boot

.PHONY: src/kernel/libkernel.a
src/kernel/libkernel.a:
	@$(MAKE) libkernel.a -C src/kernel

.PHONY: src/io/libio.a
src/io/libio.a:
	@$(MAKE) libio.a -C src/io


# target
$(target): $(libs)
	$(LD) -T $(linkscript) $(LDFLAGS) -o $(target) $(libs)
	@echo -e "Built \x1b[37;1m$@\x1b[0m"

# clean
.PHONY: clean
clean:
	rm -f $(target)
	@$(MAKE) clean -C src/boot
	@$(MAKE) clean -C src/kernel
	@$(MAKE) clean -C src/io

# qemulate
.PHONY: qemu
qemu: $(target)
	qemu-system-i386 -kernel $(target)

.PHONY: boot-check
boot-check:
	@grub-file --is-x86-multiboot $(target) && \
		echo -e "- $(target) \x1b[42;30mis valid\x1b[0m x86 multiboot"
