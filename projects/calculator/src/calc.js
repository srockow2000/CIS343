console.log("Welcome to your TypeScript Calculator");
console.log("You can perform the following operations: addition (+), subtraction (-), multiplication (*), and division (/)");
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
}
var data = require('prompt-sync')();
var op;
var x;
var y;
while (1) {
    console.log("\n\nHere was your last calculation: " +
        x + " " + op + " " + y + " = " + performCalculations(op, x, y));
    op = data("Choose an operation [+, -, *, /] or enter 'q': ");
    if (op == "q") {
        console.log("\nHave a nice day!");
        break;
    }
    if (op == "*" || op == "-" || op == "+" || op == "/") {
        console.log("\nYou chose: " + op);
        x = data("Enter your first number: ");
        y = data("Enter your second number: ");
        console.log("You entered " + x + " and " + y);
        console.log(x + " " + op + " " + y + " is equal to: " +
            performCalculations(op, x, y));
    }
    else {
        console.log("Please try again");
    }
}

