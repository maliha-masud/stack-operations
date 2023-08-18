# Stack operations
### C++ program to check validity of expressions, convert to prefix and postfix, and evaluate expressions.

**Project Description:**
* Validity of the expression is checked (correct use of brackets and operators).
* An expression of binary operators is taken as input in a character array.
* The expression is converted into prefix and postfix, and then evaluated.
* Arithmetic operators considered: +, - , / , * , ^, %
>* '^': power operator; precedence: equal to * and /; associativity: left to right.
>* '%': remainder operator; precedence: greater than * and /

**Code Description:**
* Declare a character array of size 100 and take an expression as input from the user
* Validate if the given expression is valid or not.
>* e.g. (32-(45+2) is invalid, program terminates; (120-(60+5)) is valid
* Display prefix string
* Display the postfix string with operands separated by a space
* Display result of expression evaluation
>* Input from the user = (120-(60+5))
>* Check validity: if valid:
>> Prefix: - 120 + 60 5;  Postfix: 120 60 5 + - ; Result: 55
