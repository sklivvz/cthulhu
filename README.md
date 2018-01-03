# Cthulhu
Extend Redis with JavaScript modules

![courtesy of https://www.flickr.com/photos/gwendalcentrifugue/18161295638/in/album-72157651670726983/](http://i.imgur.com/F0FwUPOl.png)

This module invokes commands from Redis in a JavaScript interpreter, `duktape`. (*the thing that should not be*)

The JavaScript commands are precompiled, can access the Redis API at a low level, and if judiciously used, can result in very good performance.

This module depends on Redis 4.0.

Issue reports and feature requests by corageous hackers are welcome. Please don't send patches just yet. Our roadmap is [here](https://github.com/sklivvz/cthulhu/blob/master/docs/roadmap.md).

## Basic Usage

You can load the module with the following [Redis call](https://github.com/antirez/redis/blob/unstable/src/modules/INTRO.md#loading-modules) (or you can use the loadmodule configuration directive):

```redis
MODULE LOAD /path/to/cthulhu.so /path/to/your/javascript.js
```

This will load and compile your JavaScript file. All the global functions you expose will be callable by any Redis client.

The module can be unloaded like any other (see the [docs](https://redis.io/topics/modules-intro#loading-modules)). Unloading a module will also unload the JavaScript context, so all work which is not saved in Redis objects will be nuked. This also allows you reload a new version of a JavaScript file, which is useful during development.

## Getting Started

For a quick introduction, please follow the instructions in our [intro](https://github.com/sklivvz/cthulhu/blob/master/docs/intro.md) document.

To build the module from source, the instructions are in our [build](https://github.com/sklivvz/cthulhu/blob/master/docs/build.md) page.

The full documentation of the Redis API, including the updated implementation status is in our [API](https://github.com/sklivvz/cthulhu/blob/master/docs/API.md) doc.

 ## Version

 The current version is 0.3.

 ## License

 [BSD 3-Clause](https://github.com/sklivvz/cthulhu/blob/master/LICENSE)
