# Tutorial

Here are are a few basic examples that should get you started.

## Hello world!

The most basic program you can run will just print "Hello world!" to the log when starting.

Create the following JavaScript file and call it `hello.js`:

```javascript
Redis.warn("Hello world!");
```

Now start your custom Redis server and connect via a client (one is conveniently compiled along with the server):

```sh
cd /path/to/custom/redis/src
./redis-server --port 7000
```

In another terminal window

```sh
cd /path/to/custom/redis/src
./redis-cli -p 7000
```

Load the module

```redis
127.0.0.1:7000> module load /path/to/cthulhu.so /path/to/hello.js
```

In your redis server window you should see something simiar to this:

```
19538:M 17 Jun 15:37:32.549 * Ready to accept connections
19538:M 17 Jun 15:37:43.525 # <cthulhu> Hello world!
19538:M 17 Jun 15:37:43.525 * Module 'cthulhu' loaded from /path/to/cthulhu.so
```

### Hello $name!

Let's try to actually export a function this time. Change your `hello.js` to read:

```javascript
function hello(name) {
    Redis.warn("Hello " + name + "!" );
}
```

Reload the module

```redis
127.0.0.1:7000> module unload cthulhu
127.0.0.1:7000> module load /path/to/cthulhu.so /path/to/hello.js
```

Now try to invoke the command passing your name

```redis
127.0.0.1:7000> invoke hello Marco
```

In the logs you should see something like

```
19538:M 17 Jun 15:43:12.845 # <cthulhu> Hello Marco!
```