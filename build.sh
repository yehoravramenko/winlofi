#!/bin/sh

mkdir -p build/
windres -J rc -O coff -i src/res/winlofi.rc -o build/winlofi.o
gcc -o build/main.o -c src/main.c -g -Werror
gcc -o build/winlofi.exe build/main.o build/winlofi.o -Wl,-subsystem,windows
