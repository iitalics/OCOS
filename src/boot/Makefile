# compilers
AS=as --32 $(gASFLAGS)
CC=gcc -m32 $(gCFLAGS)
AR=ar cr

# sources & objects
obj=.obj
srcs=$(wildcard *.s *.c)
objs=$(srcs:%=$(obj)/%.o)

libboot.a: $(obj) $(objs)
	$(AR) $@ $(objs)
	@echo -e "Built \x1b[33;1m$@\x1b[0m"

$(obj):
	mkdir $(obj)

$(obj)/%.s.o: %.s
	$(AS) $< -o $@

$(obj)/%.c.o: %.c
	$(CC) $< -c -o $@

.PHONY: clean
clean:
	rm -rf $(obj) $(wildcard *.a)
