#!/usr/bin/python
import os, re

src="src"
template = "Makefile.template"
libs = [
    # subdir       # lib
    ("src/boot",   "boot"),
    ("src/kernel", "kernel"),
    ("src/io",     "io"),
    ("src/util",   "util"),
]


templ = []
with open(template) as fh:
    for line in fh:
        templ.append(re.split("#LIBNAME#", line))

_,subdirs,_ = next(os.walk(src))

for (subdir,lib) in libs:
    with open(os.path.join(subdir, "Makefile"), "w") as fh:
        for parts in templ:
            fh.write(lib.join(parts))
    print("- generated %s/Makefile " % subdir)

with open("libs.make", "w") as fh:
    fh.write("libs = %s\n"
             % " ".join(os.path.join(subdir, "lib%s.a" % lib)
                        for (subdir,lib) in libs))
    for (subdir,lib) in libs:
        arpath = os.path.join(subdir, "lib%s.a" % lib)
        fh.write(".PHONY: %s\n" % arpath)
        fh.write("%s:\n" % arpath)
        fh.write("\t@$(MAKE) lib%s.a -C %s\n" % (lib, subdir))
        fh.write("\n")
    print("- generated libs.make")
