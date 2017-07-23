# JavaScript API

A series of JavaScript classes are available to call Redis.

* [Redis](#redis)
  * [Redis.Hash](#redishash)
  * [Redis.List](#redislist)
  * [Redis.SortedSet](#redissortedset)
      * [Redis.SortedSet.Range](#redissortedsetrange)
  * [Redis.String](#redisstring)

---

# Redis
The `Redis` global object contains the static methods to interrogate and handle 
client-wide properties of Redis. It also acts as a namespace for all the other 
classes.
## Redis.milliseconds()
Returns the current UNIX time in milliseconds.
## Redis.getClientId()
Returns the ID of the current client calling the currently active module
command. The returned ID has a few guarantees:

1. The ID is different for each different client, so if the same client
   executes a module command multiple times, it can be recognized as
   having the same ID, otherwise the ID will be different.
2. The ID increases monotonically. Clients connecting to the server later
   are guaranteed to get IDs greater than any past ID previously seen.

Valid IDs are from 1 to 2^64-1. If 0 is returned it means there was no way
to fetch the ID in the context the function was currently called.
## Redis.getSelectedDb()
Return the currently selected DB.
## Redis.setSelectedDb( db )
Changes the currently selected DB. Returns an error if the id
is out of range.

Note that the client will retain the currently selected DB even after
the Redis command implemented by the module calling this function
returns.

If the module command wishes to change something in a different DB and
returns back to the original one, it should call `Redis.getSelectedDb()`
before in order to restore the old DB number before returning.


```javascript
var oldDb = Redis.getSelectedDb();

Redis.setSelectedDb( 42 );

/*
do some work here on db 42
*/

Redis.setSelectedDb( oldDb );
```
## Redis.log( level, message )
Adds the passed `message` to the redis log with a log level of `level` (e.g. "warning").
## Redis.warn( message )
Adds the passed `message` to the redis log with a log level of `warning`.
## Redis.notice( message )
Adds the passed `message` to the redis log with a log level of `notice`.
## Redis.verbose( message )
Adds the passed `message` to the redis log with a log level of `verbose`.
## Redis.debug( message )
Adds the passed `message` to the redis log with a log level of `debug`.

## Redis.setAutoReplicate( value )
If `value` is true, all JavaScript API calls that have side effects will be replicated to all dependent slave nodes of Redis. In other words, the contents of the Redis DB should be syncronized.

Note that other pure JavaScript side effects are not replicated, so if you keep state in JavaScript, that state won't be replicated onto the slave servers.

If `value` is false, no JavaScript call will me replicated anywhere.

The default value is `false`.

## Redis.getAutoReplicate()

Returns `true` if auto replication is active, `false` otherwise.

---

# Redis.Hash
This class encapsulates a redis hash object.

``` javascript
var azathoth = new Redis.Hash("Azathoth");

azathoth.upsert("chaos", "blind"));
azathoth.insert("chaos", "idiot")); // fails, returns false

Redis.notice("Redis.Hash.length: " + azathoth.length());        // logs 1

azathoth.update("chaos", "god"));
Redis.notice("Redis.Hash.lookup: " + azathoth.lookup("chaos")); // logs "god"

azathoth.remove("chaos"));
Redis.notice("Redis.Hash.exists: " + azathoth.exists("chaos")); // logs false
```

## Redis.Hash( key )
Creates a new instance of `Redis.Hash` bound to the specified Redis key. This will not 
create a corresponding Redis hash if it is not present in the database.
## Redis.Hash.delete();
Deletes the corresponding Redis hash from the database. Returns `true` if a key was deleted.
## Redis.Hash.getExpire();
Returns the milliseconds left until the corresponding Redis hash expires or `undefined` if there is no such hash in Redis or if no timeout is set.
## Redis.Hash.length();
Returns the number of elements in the hash in Redis or `undefined` if there is no such hash.
## Redis.Hash.setExpire( milliseconds );
Sets an expiration time of `milliseconds` milliseconds on the corresponding Redis hash. Returns `undefined` if no such hash was found.
## Redis.Hash.insert( key, value )
Inserts a new element in the hash with the specified `key` as key and `value` as value. Returns `true` if a new element was inserted, and `false` if an element was already present. Ìt will return `undefined` if the hash is not found.
## Redis.Hash.upsert( key, value )
Updates the element specified by `key` with a value of `value` or inserts a new element with `key` as key if such is not found. It will return `undefined` if the hash is not found.
## Redis.Hash.update( key, value )
Updates the element specified by `key` with a value of `value` or returns `false` if such is not found. It will return `undefined` if the hash is not found.
## Redis.Hash.remove( key )
Removes the element specified by `key` from the hash and returns `true`. It will return `false` if no element was removed and `undefined` if the hash was not found.
## Redis.Hash.lookup( key )
Returns the value of the element specified by `key` or `undefined` if the hash was not found.
## Redis.Hash.exists( key )
Returns `true` if an element specified by `key` exists, `false` if it does not, or `undefined` if the hash was not found.

---

# Redis.List
A `Redis.List` object encapsulates a Redis list. It has stack-like and queue-like APIs, with semantics similar to JavaScript.

```javascript
var cthulhu = new Redis.List("Cthulhu");
cthulhu.push(1);
cthulhu.push([2,3]);

Redis.notice("Redis.List.pop(): "+ cthulhu.pop());      // logs 3

Redis.notice("Redis.List.shift(): "+ cthulhu.shift());  // logs 1

cthulhu.unshift([4,5,6]);
cthulhu.unshift(7);

Redis.notice("Redis.List.length: " + cthulhu.length()); // logs 5
```

## Redis.List( key )
Creates a new instance of `Redis.List` bound to the specified Redis key. This will not 
create a corresponding Redis list if it is not present in the database.
## Redis.List.delete();
Deletes the corresponding Redis list from the database. Returns `true` if a key was deleted.
## Redis.List.getExpire();
Returns the milliseconds left until the corresponding Redis list expires or `undefined` if there is no such list in Redis or if no timeout is set.
## Redis.List.length();
Returns the number of elements in the list in Redis or `undefined` if there is no such list.
## Redis.List.pop();
Removes the first value from the list and returns it. Returns `undefined` if no such list was found.
## Redis.List.push( value );
Adds `value` to the beginning of list and returns `true` if successful. If `value` is an array, it will push all elements in succession.
## Redis.List.setExpire( milliseconds );
Sets an expiration time of `milliseconds` milliseconds on the corresponding Redis list. Returns `undefined` if no such list was found.
## Redis.List.shift();
Removes `value` from the end of the list and returns it. Returns `undefined` if no such list was found.
## Redis.List.unshift( value );
Adds `value` at the end of the list and returns `true` if succesful. If `value` is an array, it will unshift each element in succession.

---

# Redis.SortedSet
This class represents a Redis zset class, a sorted set.

```javascript
var nyarlathotep = new Redis.SortedSet("Nyarlathotep");

nyarlathotep.upsert("atheron", 1.02));
nyarlathotep.insert("atheron", 1.04)); // fails, returns false
nyarlathotep.update("atheron", 1.04));
nyarlathotep.insinc("atheron", 0.96));
nyarlathotep.incrby("atheron", 1.0));

Redis.notice("Redis.SortedSet.length: " + nyarlathotep.length());         // logs 1
Redis.notice("Redis.SortedSet.score: " + nyarlathotep.score("atheron"));  // logs 3

nyarlathotep.remove("atheron"));
Redis.notice("Redis.SortedSet.score: " + nyarlathotep.score("atheron"));  // logs undefined
```

## Redis.SortedSet( key )
Creates a new instance of `Redis.SortedSet` bound to the specified Redis key. This will not 
create a corresponding Redis sorted set if it is not present in the database.
## Redis.SortedSet.delete();
Deletes the corresponding Redis sorted set from the database. Returns `true` if a key was deleted.
## Redis.SortedSet.getExpire();
Returns the milliseconds left until the corresponding Redis sorted set expires or `undefined` if there is no such sorted set in Redis or if no timeout is set.
## Redis.SortedSet.length();
Returns the number of elements in the sorted set in Redis or `undefined` if there is no such sorted set.
## Redis.SortedSet.setExpire( milliseconds );
Sets an expiration time of `milliseconds` milliseconds on the corresponding Redis sorted set. Returns `undefined` if no such sorted set was found.
## Redis.SortedSet.insert( key, score )
Inserts a new element in the sorted set with the specified `key` as key and `score` as score. Returns `true` if a new element was inserted, and `false` if an element was already present. Ìt will return `undefined` if the sorted set is not found.
## Redis.SortedSet.upsert( key, score )
Updates the element specified by `key` with a score of `score` or inserts a new element with `key` as key if such is not found. It will return `undefined` if the sorted set is not found.
## Redis.SortedSet.update( key, score )
Updates the element specified by `key` with a score of `score` or returns `false` if such is not found. It will return `undefined` if the sorted set is not found.
## Redis.SortedSet.incrby( key, score )
Increments the element specified by `key` by a score of `score` or returns `false` if such is not found. It will return `undefined` if the sorted set is not found.
## Redis.SortedSet.insinc( key, score )
Increments the element specified by `key` by a score of `score` or inserts a new element with `key` as key and `score` as score if such is not found. It will return `undefined` if the sorted set is not found.
## Redis.SortedSet.remove( key )
Removes the element specified by `key` from the sorted set and returns `true`. It will return `false` if no element was removed and `undefined` if the sorted set was not found.
## Redis.SortedSet.score( key )
Returns the score of the element specified by `key` or `undefined` if the sorted set was not found.
## Redis.SortedSet.getRange( config )
Returns a `Redis.SortedSet.Range` object to navigate the elements of a sorted set. Config is an object with the following properties that determine the type of range wanted:

  * `score`: if set to `false` it will sort lexically, otherwise by score
  * `reverse`: if set to `true`, it will sort descending, otherwise ascending
  * `min`: the minimumm boundary of the range, leave `undefined` to have no minimum
  * `max`: the maximum boundary of the range, leave `undefined` to have no minimum
  * `minInc`: whether the minimum boundary is inclusive (works only with scores)
  * `maxInc`: whether the maximum boundary is inclusive (works only with scores)

---

# Redis.SortedSet.Range
This class allows navingating Redis sorted sets in an easy way. This class should not be constructed by client code, it is returned by `Redis.SortedSet.getRange()`.
```javascript
var nyarlathotep = new Redis.SortedSet("Nyarlathotep");

for(var i = 0; i<100; i++) {
    nyarlathotep.upsert("atheron "+i, Math.sqrt(i));
}

var range = nyarlathotep.getRange({min:0, max:2, minInc:true});
range.each(function(elem){Redis.notice("iterating ["+elem.key+"], "+elem.score);})
range.stop();
```
## Redis.SortedSet.Range.current()
Returns the current range element as a tuple of the form `{ key, score }`.
## Redis.SortedSet.Range.previous()
Moves the current range element *back* by one element.
## Redis.SortedSet.Range.next()
Moves the current range element *forward* by one element.
## Redis.SortedSet.Range.hasNext()
Returns `true` if the sorted set has more elements to move next to.
## Redis.SortedSet.Range.each( func )
Executed the specified function `func` for each element in the set, passing each item of the range to it.
## Redis.SortedSet.Range.stop()
Terminates the current iteration. If the range is not completely enumerated you *MUST* call this method to free the corresponding key in Redis.

---

# Redis.String
The Redis.String class encapsulates a string stored in Redis.

```javascript
var rlyeh = new Redis.String("R'lyeh");

rlyeh.set("The nightmare corpse-city of R'lyeh…was built in measureless eons behind history by the vast," +      
          "loathsome shapes that seeped down from the dark stars.");
Redis.notice("Redis.String.length: " + rlyeh.length());       // logs 150

rlyeh.setExpire(10000);
Redis.notice("Redis.String.getExpire: " + rlyeh.getExpire()); // logs 10000

rlyeh.delete();
rlyeh.get();                                                // logs undefined
```
## Redis.String( key )
Creates a new instance of `Redis.String` bound to the specified Redis key. This will not 
create a corresponding Redis String if it is not present in the database.
## Redis.String.delete();
Deletes the corresponding Redis string from the database. Returns `true` if a key was deleted.
## Redis.String.get();
Returns the content of the corresponding Redis string or `undefined` if there is no corresponding
string in Redis.
## Redis.String.getExpire();
Returns the milliseconds left until the corresponding Redis string expires or `undefined` if there is no such string in Redis or if no timeout is set.
## Redis.String.length();
Returns the length of the string in Redis or `undefined` if there is no such string.
## Redis.String.set();
Sets the value of the corresponding string in Redis. If no such string exists, it creates it. It returns `true` if the operation was succesful.
## Redis.String.setExpire( milliseconds );
Sets an expiration time of `milliseconds` milliseconds on the corresponding Redis string. Returns `undefined` if no such string was found.

