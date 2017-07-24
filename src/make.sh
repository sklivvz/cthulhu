#!/bin/sh

gcc -std=gnu99 -D_GNU_SOURCE -octhulhu.so -fPIC cthulhu.c lib/duktape.c commands/commands.c commands/string.c commands/generic.c commands/hash.c commands/zset.c commands/list.c --shared 
cp cthulhu.js ../examples/
