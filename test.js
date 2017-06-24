var count = 1;

function theOldOne ( name ) {
    redisLog("warning", "redisLog works");
    redisLog("warning", "redisMilliseconds: " + redisMilliseconds());
    redisLog("warning", "redisGetClientId: " + redisGetClientId());
    redisLog("warning", "redisGetSelectedDb: " + redisGetSelectedDb());
    redisLog("warning", "redisSelectDb: " + redisSelectDb(1));
    redisListPush("cthulhu", true, 1);
    redisListPush("cthulhu", true, 2);
    redisListPush("cthulhu", true, 3);
    redisLog("warning", "redisListPop: " + redisListPop("cthulhu", false));
    redisLog("warning", "redisListPop: " + redisListPop("cthulhu", false));
    redisLog("warning", "redisListPop: " + redisListPop("cthulhu", false));
    redisLog("warning", "redisDeleteKey: " + redisDeleteKey("cthulhu"));
    redisListPush("cthulhu", true, 4);
    redisLog("warning", "redisLength of 'cthulhu': " + redisLength("cthulhu"));
    redisLog("warning", "redisSetExpire: " + redisSetExpire("cthulhu", 10000));
    redisLog("warning", "redisGetExpire: " + redisGetExpire("cthulhu"));
    redisLog("warning", "redisStringSet: " + redisStringSet("R'lyeh", "The nightmare corpse-city of R'lyeh…was built in measureless eons behind history by the vast, loathsome shapes that seeped down from the dark stars."));
    redisLog("warning", "redisStringTruncate: " + redisStringTruncate("R'lyeh", 13));
    redisLog("warning", "redisStringSet: " + redisStringGet("R'lyeh"));
    redisLog("warning", "redisHashSet: " + redisHashSet("azathoth", "chaos", "blind"));
    redisLog("warning", "redisHashSetIfAbsent: " + redisHashSetIfAbsent("azathoth", "chaos", "idiot"));
    redisLog("warning", "redisHashUpdateIfPresent: " + redisHashUpdateIfPresent("azathoth", "chaos", "god"));
    redisLog("warning", "redisHashGet: " + redisHashGet("azathoth", "chaos"));
    redisLog("warning", "redisHashUnset: " + redisHashUnset("azathoth", "chaos"));
    redisLog("warning", "redisHashIsSet: " + redisHashIsSet("azathoth", "chaos"));
    redisLog("warning", "redisHashGet: " + redisHashGet("azathoth", "fear"));
    redisLog("warning", "redisZsetAdd: " + redisZsetAdd("nyarlathotep", 1.02, "atheron"));
    redisLog("warning", "redisZsetAddIfAbsent: " + redisZsetAddIfAbsent("nyarlathotep", 1.04, "atheron"));
    redisLog("warning", "redisZsetUpdateIfPresent: " + redisZsetUpdateIfPresent("nyarlathotep", 1.04, "atheron"));
    redisLog("warning", "redisZsetIncrby: " + redisZsetIncrby("nyarlathotep", 0.96, "atheron"));
    redisLog("warning", "redisZsetIncrbyIfAbsent: " + redisZsetIncrbyIfAbsent("nyarlathotep", 1.04, "atheron"));
    redisLog("warning", "redisZsetIncrbyIfPresent: " + redisZsetIncrbyIfPresent("nyarlathotep", 1.0, "atheron"));
    redisLog("warning", "redisZsetScore: " + redisZsetScore("nyarlathotep", "atheron"));
    redisLog("warning", "redisZsetRem: " + redisZsetRem("nyarlathotep", "atheron"));
    redisLog("warning", "redisZsetScore: " + redisZsetScore("nyarlathotep", "atheron"));
    redisLog("warning", "redisZsetRem: " + redisZsetRem("nyarlathotep", "atheron"));


    return "Hi " + name + ". In JavaScript land it's " + 
        new Date() + "\nYou invoked the old one " + count++ + " times.\n";
}

function test() {
    Redis.warn("Starting the test");
    Redis.warn("Redis.milliseconds(): " + Redis.milliseconds());
    Redis.warn("Redis.clientId(): " + Redis.clientId());
    Redis.warn("Redis.getSelectedDb(): " + Redis.getSelectedDb());
    Redis.warn("Redis.setSelectedDb(1): " + Redis.setSelectedDb(1));

    var rlyeh = new Redis.String("R'lyeh");
    Redis.warn("Redis.String.set: " + rlyeh.set("The nightmare corpse-city of R'lyeh…was built in measureless eons behind history by the vast, loathsome shapes that seeped down from the dark stars."));
    Redis.warn("Redis.String.length: " + rlyeh.length());
    Redis.warn("Redis.String.setExpire: " + rlyeh.setExpire(10000));
    Redis.warn("Redis.String.getExpire: " + rlyeh.getExpire());
    Redis.warn("Redis.String.truncate: " + rlyeh.truncate(13));
    Redis.warn("Redis.String.length: " + rlyeh.length());
    Redis.warn("Redis.String.get: " + rlyeh.get());
    Redis.warn("Redis.String.delete: " + rlyeh.delete());
    Redis.warn("Redis.String.get: " + rlyeh.get());

    var cthulhu = new Redis.List("Cthulhu");
    Redis.warn("Redis.List.push(1): " + cthulhu.push(1));
    Redis.warn("Redis.List.push([2,3]): "+ cthulhu.push([2,3]));
    Redis.warn("Redis.List.pop(): "+ cthulhu.pop());
    Redis.warn("Redis.List.shift(): "+ cthulhu.shift());
    Redis.warn("Redis.List.unshift([4,5,6]): "+ cthulhu.unshift([4,5,6]));
    Redis.warn("Redis.List.unshift(7): "+ cthulhu.unshift(7));
    Redis.warn("Redis.List.length: " + cthulhu.length());
    Redis.warn("Redis.List.setExpire: " + cthulhu.setExpire(12345));
    Redis.warn("Redis.List.getExpire: " + cthulhu.getExpire());
    Redis.warn("Redis.List.delete: " + cthulhu.delete());
    Redis.warn("Redis.List.length: " + cthulhu.length());

    var azathoth = new Redis.Hash("Azathoth");
    Redis.warn("Redis.Hash.upsert: " + azathoth.upsert("chaos", "blind"));
    Redis.warn("Redis.Hash.insert: " + azathoth.insert("chaos", "idiot"));
    Redis.warn("Redis.Hash.length: " + azathoth.length());
    Redis.warn("Redis.Hash.setExpire: " + azathoth.setExpire(5432));
    Redis.warn("Redis.Hash.getExpire: " + azathoth.getExpire());
    Redis.warn("Redis.Hash.update: " + azathoth.update("chaos", "god"));
    Redis.warn("Redis.Hash.lookup: " + azathoth.lookup("chaos"));
    Redis.warn("Redis.Hash.remove: " + azathoth.remove("chaos"));
    Redis.warn("Redis.Hash.exists: " + azathoth.exists("chaos"));
    Redis.warn("Redis.Hash.delete: " + azathoth.delete());
    Redis.warn("Redis.Hash.lookup: " + azathoth.lookup("fear"));

    var nyarlathotep = new Redis.SortedSet("Nyarlathotep");
    Redis.warn("Redis.SortedSet.upsert: " + nyarlathotep.upsert("atheron", 1.02));
    Redis.warn("Redis.SortedSet.insert: " + nyarlathotep.insert("atheron", 1.04));
    Redis.warn("Redis.SortedSet.update: " + nyarlathotep.update("atheron", 1.04));
    Redis.warn("Redis.SortedSet.insinc: " + nyarlathotep.insinc("atheron", 0.96));
    Redis.warn("Redis.SortedSet.incrby: " + nyarlathotep.incrby("atheron", 1.0));
    Redis.warn("Redis.SortedSet.length: " + nyarlathotep.length());
    Redis.warn("Redis.SortedSet.setExpire: " + nyarlathotep.setExpire(5432));
    Redis.warn("Redis.SortedSet.getExpire: " + nyarlathotep.getExpire());
    Redis.warn("Redis.SortedSet.score: " + nyarlathotep.score("atheron"));
    Redis.warn("Redis.SortedSet.remove: " +nyarlathotep.remove("atheron"));
    Redis.warn("Redis.SortedSet.score: " + nyarlathotep.score("atheron"));
    Redis.warn("Redis.SortedSet.delete: " + nyarlathotep.delete());
    Redis.warn("Redis.SortedSet.remove: " + nyarlathotep.remove("atheron"));

    var nyarlathotep = new Redis.SortedSet("Nyarlathotep");
    for(var i = 0; i<100; i++) {
        nyarlathotep.upsert("atheron "+i, Math.sqrt(i));
    }
    var range = nyarlathotep.getRange({min:0, max:2, minInc:true});
    range.each(function(elem){Redis.warn("iterating ["+elem.key+"], "+elem.score);})
    range.stop();
    

}