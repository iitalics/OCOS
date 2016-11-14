#!/usr/bin/python
import os, re

src="src"
template = "Makefile.template"

templ = []
with open(template) as fh:
    for line in fh:
        templ.append(re.split("#LIBNAME#", line))

_,subdirs,_ = next(os.walk(src))

for d in subdirs:
    with open(os.path.join(src, d, "Makefile"), "w") as fh:
        for parts in templ:
            fh.write(d.join(parts))
    print("- generated Makefile for: " + d)
    
