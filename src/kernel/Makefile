# compilers
AS=as --32 $(gASFLAGS)
CC=gcc -m32 $(gCFLAGS)
CXX=g++ -m32 $(gCXXFLAGS)
AR=ar cr

# sources & objects
obj=.obj
srcs=$(wildcard *.s *.c *.cpp)
objs=$(srcs:%=$(obj)/%.o)

libkernel.a: $(obj) $(objs)
	$(AR) $@ $(objs)
	@echo -e "Built \x1b[33;1m$@\x1b[0m"

$(obj):
	mkdir $(obj)

-include $(wildcard .*.dep)

$(obj)/%.s.o: %.s
	$(AS) $< -o $@

$(obj)/%.c.o: %.c
	$(CC) $< -c -o $@
	@$(CC) $< -MM -MT $@ -o .$<.dep

$(obj)/%.cpp.o: %.cpp
	$(CXX) $< -c -o $@
	@$(CXX) $< -MM -MT $@ -o .$<.dep

.PHONY: clean
clean:
	rm -rf $(obj) $(wildcard .*.dep)
