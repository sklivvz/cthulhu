var count = 1;

function theOldOne ( name ) {
    redisListPush("cthulhu", true, name + count);

    redisLog("warning", "fhtagn");

    //redisLog("warning", "a"+redisMilliseconds());

    return "Hi " + name + ". In JavaScript land it's " + 
        new Date() + "\nYou invoked the old one " + count++ + " times.\n";
    }
