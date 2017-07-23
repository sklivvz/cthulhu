function test() {
    Redis.notice("Starting the test");

    Redis.setAutoReplication(true);
    Redis.notice("Auto Replication: "+ Redis.getAutoReplication());

    var rand = new Redis.String("RANDOM");
    rand.set(Math.random());
    Redis.notice("'RANDOM' set to '"+rand.get()+"'");
    
    Redis.notice("Redis.milliseconds(): " + Redis.milliseconds());
    Redis.notice("Redis.clientId(): " + Redis.clientId());
    Redis.notice("Redis.getSelectedDb(): " + Redis.getSelectedDb());
    Redis.notice("Redis.setSelectedDb(1): " + Redis.setSelectedDb(1));

    var rlyeh = new Redis.String("R'lyeh");
    Redis.notice("Redis.String.set: " + rlyeh.set("The nightmare corpse-city of R'lyeh…was built in measureless eons behind history by the vast, loathsome shapes that seeped down from the dark stars."));
    Redis.notice("Redis.String.length: " + rlyeh.length());
    Redis.notice("Redis.String.setExpire: " + rlyeh.setExpire(10000));
    Redis.notice("Redis.String.getExpire: " + rlyeh.getExpire());
    Redis.notice("Redis.String.length: " + rlyeh.length());
    Redis.notice("Redis.String.get: " + rlyeh.get());
    Redis.notice("Redis.String.delete: " + rlyeh.delete());
    Redis.notice("Redis.String.get: " + rlyeh.get());

    var cthulhu = new Redis.List("Cthulhu");
    Redis.notice("Redis.List.push(1): " + cthulhu.push(1));
    Redis.notice("Redis.List.push([2,3]): "+ cthulhu.push([2,3]));
    Redis.notice("Redis.List.pop(): "+ cthulhu.pop());
    Redis.notice("Redis.List.shift(): "+ cthulhu.shift());
    Redis.notice("Redis.List.unshift([4,5,6]): "+ cthulhu.unshift([4,5,6]));
    Redis.notice("Redis.List.unshift(7): "+ cthulhu.unshift(7));
    Redis.notice("Redis.List.length: " + cthulhu.length());
    Redis.notice("Redis.List.setExpire: " + cthulhu.setExpire(12345));
    Redis.notice("Redis.List.getExpire: " + cthulhu.getExpire());
    Redis.notice("Redis.List.delete: " + cthulhu.delete());
    Redis.notice("Redis.List.length: " + cthulhu.length());

    var azathoth = new Redis.Hash("Azathoth");
    Redis.notice("Redis.Hash.upsert: " + azathoth.upsert("chaos", "blind"));
    Redis.notice("Redis.Hash.insert: " + azathoth.insert("chaos", "idiot"));
    Redis.notice("Redis.Hash.length: " + azathoth.length());
    Redis.notice("Redis.Hash.setExpire: " + azathoth.setExpire(5432));
    Redis.notice("Redis.Hash.getExpire: " + azathoth.getExpire());
    Redis.notice("Redis.Hash.update: " + azathoth.update("chaos", "god"));
    Redis.notice("Redis.Hash.lookup: " + azathoth.lookup("chaos"));
    Redis.notice("Redis.Hash.remove: " + azathoth.remove("chaos"));
    Redis.notice("Redis.Hash.exists: " + azathoth.exists("chaos"));
    Redis.notice("Redis.Hash.delete: " + azathoth.delete());
    Redis.notice("Redis.Hash.lookup: " + azathoth.lookup("fear"));

    var nyarlathotep = new Redis.SortedSet("Nyarlathotep");
    Redis.notice("Redis.SortedSet.upsert: " + nyarlathotep.upsert("atheron", 1.02));
    Redis.notice("Redis.SortedSet.insert: " + nyarlathotep.insert("atheron", 1.04));
    Redis.notice("Redis.SortedSet.update: " + nyarlathotep.update("atheron", 1.04));
    Redis.notice("Redis.SortedSet.insinc: " + nyarlathotep.insinc("atheron", 0.96));
    Redis.notice("Redis.SortedSet.incrby: " + nyarlathotep.incrby("atheron", 1.0));
    Redis.notice("Redis.SortedSet.length: " + nyarlathotep.length());
    Redis.notice("Redis.SortedSet.setExpire: " + nyarlathotep.setExpire(5432));
    Redis.notice("Redis.SortedSet.getExpire: " + nyarlathotep.getExpire());
    Redis.notice("Redis.SortedSet.score: " + nyarlathotep.score("atheron"));
    Redis.notice("Redis.SortedSet.remove: " +nyarlathotep.remove("atheron"));
    Redis.notice("Redis.SortedSet.score: " + nyarlathotep.score("atheron"));
    Redis.notice("Redis.SortedSet.delete: " + nyarlathotep.delete());
    Redis.notice("Redis.SortedSet.remove: " + nyarlathotep.remove("atheron"));

    for(var i = 0; i<100; i++) {
        nyarlathotep.upsert("atheron "+i, Math.sqrt(i));
    }
    var range = nyarlathotep.getRange({min:0, max:2, minInc:true});
    range.each(function(elem){Redis.notice("iterating ["+elem.key+"], "+elem.score);})
}