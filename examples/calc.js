var calc = new Redis.List("calc");

function c(input) {
    switch(input)
    {
        case "+":
            calc.push(calc.pop()+calc.pop());
            return calc.length();
        case "-":
            calc.push(calc.pop()-calc.pop());
            return calc.length();
        case "*":
            calc.push(calc.pop()*calc.pop());
            return calc.length();
        case "/":
            calc.push(1/calc.pop()*calc.pop());
            return calc.length();
        case "=":
            return calc.pop()|0;
        case "c":
        case "C":
            calc.delete();
            return 0;
        default:
            calc.push(input);
            return calc.length();
    }
}
