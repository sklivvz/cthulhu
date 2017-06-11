#!/bin/sh

gcc -std=c99 -octhulhu.so -fPIC cthulhu.c duktape.c --shared