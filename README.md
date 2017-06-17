# Cthulhu
Extend Redis with JavaScript modules

![](https://c1.staticflickr.com/9/8758/18161295638_6fc93ec641_b.jpg)

This module *invokes commands* from Redis in a JavaScript interpreter (*the thing that should not be*)

The JavaScript commands are precompiled, can access the Redis API at a low level, and if judiciously used, can result in very good performance.

This module depends on Redis 4.0, which is still unstable software and a pending patch. Being alpha itself, API compatibility is not yet guaranteed.

Issue reports and feature requests by corageous hackers are welcome. Please don't send patches just yet.

## How to build

### Linux

Get a patched version of Redis from [my fork](https://github.com/sklivvz/redis) and compile according to instructions.

Download or clone this repository and compile with `./make`: the `cthulhu.so` library generated is what you need to reference in Redis to make this work.

### Non Linux

Not supported yet.

## How to use

You can load the module with the following [Redis call](https://github.com/antirez/redis/blob/unstable/src/modules/INTRO.md#loading-modules) (or you can use the loadmodule configuration directive):

~~~redis
MODULE LOAD /path/to/cthulhu.so /path/to/your/javascript.js
~~~

This will load and compile your JavaScript file. All the global functions you expose will be callable by any Redis client.

The module can be unloaded like any other (see the [docs](https://github.com/antirez/redis/blob/unstable/src/modules/INTRO.md#loading-modules)). Unloading a module will also unload the JavaScript context, so all work which is not saved in Redis objects will be nuked. This also allows you reload a new version of a JavaScript file, which is useful during development.

### Hello world!

The most basic program you can run will just print "Hello world!" to the log when starting.

Create the following JavaScript file and call it `hello.js`:

~~~javascript
redisLog("warning", "Hello world!");
~~~

Now start your custom Redis server and connect via a client (one is conveniently compiled along with the server):

~~~sh
cd /path/to/custom/redis/src
./redis-server --port 7000
~~~

In another terminal window

~~~sh
cd /path/to/custom/redis/src
./redis-cli -p 7000
~~~

Load the module

~~~redis
127.0.0.1:7000> module load /path/to/cthulhu.so /path/to/hello.js
~~~

In your redis server window you should see something simiar to this:

~~~
19538:M 17 Jun 15:37:32.549 * Ready to accept connections
19538:M 17 Jun 15:37:43.525 # <cthulhu> Hello world!
19538:M 17 Jun 15:37:43.525 * Module 'cthulhu' loaded from /path/to/cthulhu.so
~~

### Hello $name!

Let's try to actually export a function this time. Change your `hello.js` to read:

~~~javascript
function hello(name) {
    redisLog("warning", "Hello " + name + "!" );
}
~~~

Reload the module

~~~redis
127.0.0.1:7000> module unload cthulhu
127.0.0.1:7000> module load /path/to/cthulhu.so /path/to/hello.js
~~~

Now try to invoke the command passing your name

~~~redis
127.0.0.1:7000> invoke hello Marco
~~~

In the logs you should see something like

~~~
19538:M 17 Jun 15:43:12.845 # <cthulhu> Hello Marco!
~~~

## Redis API

In version 0.1 I will be exposing the following `RedisModule` API in the global javascript object.

 * [x] redisMilliseconds()
 * [x] redisGetClientId()
 * [x] redisGetSelectedDb()
 * [x] redisSelectDb( db )
 * [x] redisLength( key )
 * [x] redisDeleteKey( key )
 * [x] redisGetExpire( key )
 * [x] redisSetExpire( key, milliseconds )
 * [x] redisStringSet( key, value )
 * [x] redisStringTruncate( key, length )
 * [x] redisStringGet( key )
 * [x] redisListPush( key, at_head, value)
 * [x] redisListPop( key, from_head )
 * [x] redisZsetAdd( key, amount, element )
 * [x] redisZsetUpdateIfPresent( key, amount, element )
 * [x] redisZsetAddIfAbsent( key, amount, element )
 * [x] redisZsetIncrby( key, amount, element )
 * [x] redisZsetIncrbyIfPresent( key, amount, element )
 * [x] redisZsetIncrbyIfAbsent( key, amount, element )
 * [x] redisZsetRem( key, element )
 * [x] redisZsetScore( key, element )
 * [ ] redisZsetRangeStop
 * [ ] redisZsetRangeEndReached
 * [ ] redisZsetFirstInScoreRange
 * [ ] redisZsetLastInScoreRange
 * [ ] redisZsetFirstInLexRange
 * [ ] redisZsetLastInLexRange
 * [ ] redisZsetRangeCurrentElement
 * [ ] redisZsetRangeNext
 * [ ] redisZsetRangePrev
 * [x] redisHashSet( key, hashKey, hashValue )
 * [x] redisHashSetIfPresent( key, hashKey, hashValue )
 * [x] redisHashSetIfAbsent( key, hashKey, hashValue )
 * [x] redisHashUnset( key, hashKey )
 * [x] redisHashIsSet( key, hashKey )
 * [x] redisHashGet( key, hashKey )
 * [x] redisLog( level, message )

 They are documented in the [Redis Module API page](https://github.com/antirez/redis/blob/unstable/src/modules/API.md)

### Roadmap

* create an actual JavaScript API and not simply global methods
* blocking calls/background processing
* functions with variable argument number
* return type to redis should be specific and not string
* support for generic LUA style calls

 ## Version

 The current version is 0.0.

 ## License

 [BSD 3-Clause](https://github.com/sklivvz/cthulhu/blob/master/LICENSE)