libs = src/boot/libboot.a src/kernel/libkernel.a src/io/libio.a src/util/libutil.a
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

