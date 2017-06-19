# JavaScript API

A series of JavaScript classes are available to call Redis. Documentation to follow.

# Redis API

There is also a lower level API. This will be subject to change until further notice.

The following `RedisModule` API in are exposed the global javascript object. The checked boxes mark what is implemented.

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
 * [x] redisZsetRangeStop( handle )
 * [x] redisZsetRangeEndReached( handle )
 * [x] redisZsetFirstInScoreRange( key, min, max, mininc, maxinc )
 * [x] redisZsetLastInScoreRange( key, min, max, mininc, maxinc )
 * [x] redisZsetFirstInLexRange( key, min, max )
 * [x] redisZsetLastInLexRange( key, min, max )
 * [x] redisZsetRangeCurrentElement( handle )
 * [x] redisZsetRangeNext( handle )
 * [x] redisZsetRangePrev( handle )
 * [x] redisHashSet( key, hashKey, hashValue )
 * [x] redisHashSetIfPresent( key, hashKey, hashValue )
 * [x] redisHashSetIfAbsent( key, hashKey, hashValue )
 * [x] redisHashUnset( key, hashKey )
 * [x] redisHashIsSet( key, hashKey )
 * [x] redisHashGet( key, hashKey )
 * [x] redisLog( level, message )

 They are documented in the [Redis Module API page](https://github.com/antirez/redis/blob/unstable/src/modules/API.md)
