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

    return "Hi " + name + ". In JavaScript land it's " + 
        new Date() + "\nYou invoked the old one " + count++ + " times.\n";
}
