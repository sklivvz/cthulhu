var count = 1;

function theOldOne ( name ) {
    redisLog("warning", "redisLog works");
    redisLog("warning", "redisMilliseconds: " + redisMilliseconds());
    redisLog("warning", "redisGetClientId: " + redisGetClientId());
    redisLog("warning", "redisGetSelectedDb: " + redisGetSelectedDb());
    redisLog("warning", "redisSelectDb: ", redisSelectDb(1));
    redisListPush("cthulhu", true, name + count);

    return "Hi " + name + ". In JavaScript land it's " + 
        new Date() + "\nYou invoked the old one " + count++ + " times.\n";
    }
