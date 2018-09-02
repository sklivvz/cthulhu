var calc = new Redis.List("calc");

function c(input) {

	// defined locally so it won't be exposed to the API
	function pop(){
		return parseInt(calc.pop());
	}
	
    switch(input)
    {
        case "+":
            calc.push(pop()+pop());
            return calc.length();
        case "-":
            calc.push(pop()-pop());
            return calc.length();
        case "*":
            calc.push(pop()*pop());
            return calc.length();
        case "/":
            calc.push(1/pop()*pop());
            return calc.length();
        case "=":
            return pop()|0;
        case "c":
        case "C":
            calc.delete();
            return 0;
        default:
            calc.push(input);
            return calc.length();
    }
}
