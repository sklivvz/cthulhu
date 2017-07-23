/*
 * cthulu.js - JavaScript classes wrap for basic Redis calls. 
 * This should be in the same folder as your javascript file.
 */

// Copyright 2017 Marco Cecconi
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

var Redis = {};

// Static global methods
Redis.milliseconds = function () { return redisMilliseconds(); }
Redis.clientId = function() { return redisGetClientId(); }
Redis.getSelectedDb = function() { return redisGetSelectedDb(); }
Redis.setSelectedDb = function(number) { return redisSelectDb(number); }
Redis.log = function(logLevel,message) { return redisLog(loglevel,message); }
Redis.warn = function(message) { return redisLog("warning",message); }
Redis.notice = function(message) { return redisLog("notice",message); }
Redis.verbose = function(message) { return redisLog("verbose",message); }
Redis.debug = function(message) { return redisLog("debug",message); }
Redis.getAutoReplication = function(value) { return redisGetAutoReplication(); }
Redis.setAutoReplication = function(value) { return redisSetAutoReplication(value); }

// Base class with all shared object methods

Redis.Object = function(name) {
    this.key = name;
    this.arrayApply = function(value,fun) {
        if (value instanceof Array) {
            // this can be optimized with better API support
            var i, n, e, r = true;
            for (i = 0, n = value.length; i < n; i++) {
                r = r && fun.call(this,value[i]);
            }
            return r;
        }
        return fun.call(this,value);
    }
}
Redis.Object.prototype.length = function() { return redisLength(this.key); }
Redis.Object.prototype.getName = function() { return this.key; }
Redis.Object.prototype.delete = function() { return redisDeleteKey(this.key); }
Redis.Object.prototype.getExpire = function() { return redisGetExpire(this.key); }
Redis.Object.prototype.setExpire = function(milliseconds) { return redisSetExpire(this.key, milliseconds); }

// String

Redis.String = function(name) {
    Redis.Object.call(this, name);
}
Redis.String.prototype = Object.create(Redis.Object.prototype);
Redis.String.prototype.constructor = Redis.String;
Redis.String.prototype.set = function(value) { return redisStringSet(this.key,value); }
Redis.String.prototype.get = function() { return redisStringGet(this.key); }

// List

Redis.List = function(name) {
    Redis.Object.call(this, name);
}
Redis.List.prototype = Object.create(Redis.Object.prototype);
Redis.List.prototype.constructor = Redis.List;
Redis.List.prototype.push = function(value) { this.arrayApply(value, function(i){return redisListPush(this.key,false,i);})}
Redis.List.prototype.pop = function() { return redisListPop(this.key,false); }
Redis.List.prototype.unshift = function(value) { this.arrayApply(value, function(i){return redisListPush(this.key,true,i);})}
Redis.List.prototype.shift = function() { return redisListPop(this.key,true); }


// Hash

Redis.Hash = function(name) {
    Redis.Object.call(this, name);
}
Redis.Hash.prototype = Object.create(Redis.Object.prototype);
Redis.Hash.prototype.constructor = Redis.Hash;
Redis.Hash.prototype.insert = function(key,value) { return redisHashSetIfAbsent(this.key,key,value); }
Redis.Hash.prototype.upsert = function(key,value) { return redisHashSet(this.key,key,value); }
Redis.Hash.prototype.update = function(key,value) { return redisHashUpdateIfPresent(this.key,key,value); }
Redis.Hash.prototype.remove = function(key) { return redisHashUnset(this.key,key); }
Redis.Hash.prototype.lookup = function(key) { return redisHashGet(this.key,key); }
Redis.Hash.prototype.exists = function(key) { return redisHashIsSet(this.key,key); }

// Sorted Set

Redis.SortedSet = function(name) {
    Redis.Object.call(this, name);
    Range = function(key,config){
        this.keyPtr = undefined;
        config |= {};
        this.config = {};
        this.config.reverse = false;
        if (config.reverse != undefined)
            this.config.reverse = config.reverse;
        this.config.score = config.score === false ? false : true;
        this.config.min = config.min || undefined;
        this.config.max = config.max || undefined;
        if (this.config.score) {
            this.config.minInc = config.minInc || false;
            this.config.maxInc = config.maxInc || false;
            if (this.config.reverse) {
                this.keyPtr = redisZsetLastInScoreRange(key, this.config.min, this.config.max, this.config.minInc, this.config.maxInc);
            } else {
                this.keyPtr = redisZsetFirstInScoreRange(key, this.config.min, this.config.max, this.config.minInc, this.config.maxInc);
            }
        } else {
            if (this.config.reverse) {
                this.keyPtr = redisZsetLastInLexRange(key, this.config.min, this.config.max);
            } else {
                this.keyPtr = redisZsetFirstInLexRange(key, this.config.min, this.config.max);
            }
        }
        return this;
    }
    Range.prototype = {
        current: function() {
            return redisZsetRangeCurrentElement(this.keyPtr);
        },
        previous: function() {
            return redisZsetRangePrev(this.keyPtr);
        },
        next: function() {
            return redisZsetRangeNext(this.keyPtr);
        },
        hasNext: function() {
            return !redisZsetRangeEndReached(this.keyPtr);
        },
        each: function(callback) {
            if (this.keyPtr == undefined) return undefined;
            var item;
            while(this.next()) {
                item = this.current();
                callback(item);
            }
            return true;
        },
        stop: function() {
            if (this.keyPtr == undefined) return;
            redisZsetRangeStop(this.keyPtr);
            this.keyPtr == undefined;
        }
    }
    Duktape.fin(Range.prototype, function (x) {
    if (x === Range.prototype) {
        return;  // called for the prototype itself
    }
    try {
        x.stop();
    } catch (e) {
        redisLog("warning","finalizer failed for range (ignoring): " + e);
    }
    delete x.fd;
});
}
Redis.SortedSet.prototype = Object.create(Redis.Object.prototype);
Redis.SortedSet.prototype.constructor = Redis.SortedSet;
Redis.SortedSet.prototype.insert = function(key,value) { return redisZsetAddIfAbsent(this.key,value,key); }
Redis.SortedSet.prototype.upsert = function(key,value) { return redisZsetAdd(this.key,value,key); }
Redis.SortedSet.prototype.update = function(key,value) { return redisZsetUpdateIfPresent(this.key,value,key); }
Redis.SortedSet.prototype.insinc = function(key,value) { return redisZsetIncrby(this.key,value,key); }
Redis.SortedSet.prototype.incrby = function(key,value) { return redisZsetIncrbyIfPresent(this.key,value,key); }
Redis.SortedSet.prototype.remove = function(key) { return redisZsetRem(this.key,key); }
Redis.SortedSet.prototype.score = function(key) { return redisZsetScore(this.key,key); }
Redis.SortedSet.prototype.getRange = function(config) { return new Range(this.key,config); }