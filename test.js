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


    return "Hi " + name + ". In JavaScript land it's " + 
        new Date() + "\nYou invoked the old one " + count++ + " times.\n";
}
