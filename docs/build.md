# How to build

## Linux

Get a patched version of Redis from [my fork](https://github.com/sklivvz/redis) and compile according to instructions.

Download or clone this repository and compile with `cd src && ./make.sh`: the `cthulhu.so` library generated is what you need to reference in Redis to make this work. `cthulhu.js` needs to be included in the folder next to the javascript you want to load.

## Non Linux

Not supported yet.
