function DeleteTop(name, num) {
    var set = new Redis.SortedSet(name);
    var i = 0;
    var range = set.getRange();
    range.each(function(elem){
        if (i++<10) {
            set.remove(elem.key);
        }
    });
}