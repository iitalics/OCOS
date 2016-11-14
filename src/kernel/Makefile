# compilers
AS=as --32 $(gASFLAGS)
CC=gcc -m32 $(gCFLAGS)
CXX=g++ -m32 $(gCXXFLAGS)
AR=ar cr

# sources & objects
obj=.obj
srcs=$(shell find * -regex '.*\.\(c\|s\|cpp\)')
objs=$(srcs:%=$(obj)/%.o)
objdirs=$(patsubst %,.obj/%,$(shell find * -type d -not -name $(obj)))

libkernel.a: $(objdirs) $(obj) $(objs)
	$(AR) $@ $(objs)
	@echo -e "Built library \x1b[33;1m-kernel-\x1b[0m"

$(obj):
	mkdir -p $@
$(obj)/%:
	mkdir -p $@

-include $(wildcard $(obj)/*.dep)

$(obj)/%.s.o: %.s
	$(AS) $< -o $@

$(obj)/%.c.o: %.c
	$(CC) $< -c -o $@
	@$(CC) $< -MM -MT $@ -o $(obj)/$<.dep

$(obj)/%.cpp.o: %.cpp
	$(CXX) $< -c -o $@
	@$(CXX) $< -MM -MT $@ -o $(obj)/$<.dep

.PHONY: clean
clean:
	rm -rf $(obj) kernel.a
