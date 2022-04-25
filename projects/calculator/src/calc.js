console.log("Welcome to your TypeScript Calculator");
console.log("You can perform the following operations: addition (+), subtraction (-), multiplication (*), division (/), and exponentiation (^).");
function performCalculations(operation, x, y) {
    if (operation == "+") {
        // the extra + operator is to make sure that x and y are added as numbers, not strings
        return (+x + +y);
    }
    if (operation == "-") {
        return (x - y);
    }
    if (operation == "*") {
        return (x * y);
    }
    if (operation == "/") {
        if (y == 0) {
            return 0;
        }
        return (x / y);
    }
    if (operation == "^") {
        return Math.pow(x, y);
    }
}
var data = require('prompt-sync')();
var lastCalc = "";
var op;
var x;
var y;
var result;
while (1) {
    if (lastCalc != "") {
        console.log("\n\nHere was your last calculation: " +
            x + " " + op + " " + y + " = " + lastCalc);
    }
    op = data("Choose an operation [+, -, *, /, ^] or enter 'q': ");
    if (op == "q") {
        console.log("\nHave a nice day!");
        break;
    }
    if (op == "*" || op == "-" || op == "+" || op == "/" || op == "^") {
        console.log("\nYou chose: " + op);
        if (result == 'y') {
            x = lastCalc;
            console.log("Your first number is: " + x);
        }
        else {
            x = data("Enter your first number: ");
        }
        y = data("Enter your second number: ");
        console.log("You entered " + x + " and " + y);
        lastCalc = performCalculations(op, x, y);
        console.log(x + " " + op + " " + y + " is equal to: " + lastCalc);
        result = data("If you would like to use your result [" + lastCalc + "], enter 'y' ");
    }
    else {
        console.log("Please try again");
    }
}
