target=OCOS.bin
bin: $(target)
all: makefiles $(target) boot-check qemu

wd:=$(shell pwd)

# global compiler flags
optimize=-O2
c_like=-I$(wd)/src -nostdlib $(optimize) -Wall -fno-asynchronous-unwind-tables

gCC = gcc
gASFLAGS = $(c_like)
gCFLAGS = $(c_like) -std=c99
gCXXFLAGS = $(c_like) -std=c++11 -fno-exceptions -fno-rtti
export gCC
export gASFLAGS
export gCFLAGS
export gCXXFLAGS

# linker
linkscript=src/linker.ld
LD=gcc -m32 -ffreestanding
LDFLAGS=-O2 -nostdlib -Wl,--build-id=none
ifdef CYGWIN_BUILD
LDFLAGS += -fno-leading-underscores
endif

# libraries
libs = src/boot/libboot.a \
	src/kernel/libkernel.a \
	src/io/libio.a \
	src/util/libutil.a

.PHONY: src/boot/libboot.a
src/boot/libboot.a:
	@$(MAKE) libboot.a -C src/boot

.PHONY: src/kernel/libkernel.a
src/kernel/libkernel.a:
	@$(MAKE) libkernel.a -C src/kernel

.PHONY: src/io/libio.a
src/io/libio.a:
	@$(MAKE) libio.a -C src/io

.PHONY: src/util/libutil.a
src/util/libutil.a:
	@$(MAKE) libutil.a -C src/util

# makefiles
PYTHON=python2
.PHONY: makefiles
makefiles:
	$(PYTHON) gen-makefiles.py

# target
$(target): $(libs)
	$(LD) -T $(linkscript) $(LDFLAGS) -o $(target) $(libs)
	@echo -e "Linked \x1b[37;1m$@\x1b[0m"

# clean
.PHONY: clean
clean:
	rm -f $(target)
	@$(MAKE) clean -C src/boot
	@$(MAKE) clean -C src/kernel
	@$(MAKE) clean -C src/io
	@$(MAKE) clean -C src/util

# qemulate
qemu_memory = 1G
.PHONY: qemu
qemu: $(target)
	qemu-system-i386 -kernel $(target) -m $(qemu_memory) 2>/dev/null

.PHONY: boot-check
boot-check:
	@grub-file --is-x86-multiboot $(target) && \
		echo -e "- $(target) \x1b[42;30mis valid\x1b[0m x86 multiboot" || \
		echo -e "- $(target) \x1b[41;37;1mnot valid\x1b[0m x86 multboot"
