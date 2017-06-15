function c(input) {
    switch(input)
    {
        case "+":
            var first = redisListPop("calc", true)|0;
            var second = redisListPop("calc", true)|0;
            var result = first + second;
            redisListPush("calc", true, result);
            return redisLength("calc");
        case "-":
            var first = redisListPop("calc", true)|0;
            var second = redisListPop("calc", true)|0;
            var result = first - second;
            redisListPush("calc", true, result);
            return redisLength("calc");
        case "*":
            var first = redisListPop("calc", true)|0;
            var second = redisListPop("calc", true)|0;
            var result = first * second;
            redisListPush("calc", true, result);
            return redisLength("calc");
        case "/":
            var first = redisListPop("calc", true)|0;
            var second = redisListPop("calc", true)|0;
            var result = second/first;
            redisListPush("calc", true, result);
            return redisLength("calc");
        case "=":
            return redisListPop("calc", true)|0;
        case "c":
        case "C":
            redisDeleteKey("calc");
            return redisLength("calc");
        default:
            redisListPush("calc", true, input);
            return redisLength("calc");
    }
}
