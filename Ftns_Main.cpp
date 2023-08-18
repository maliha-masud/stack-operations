//A2.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Classes.cpp"
#include <iostream>
using namespace std;

bool CheckValidity(char expression[]) { //function to validate if use of brackets and operators is correct
    int size = 0;
    
    //all characters must be integer operands or operators
    for (int i = 0; expression[i] != '\0'; i++)
    {
        size++; //get size for later use
        if (expression[i] != '0' && expression[i] != '1' && expression[i] != '2' && expression[i] != '3'
            && expression[i] != '4' && expression[i] != '5' && expression[i] != '6' && expression[i] != '7'
            && expression[i] != '8' && expression[i] != '9' && expression[i] != '+' && expression[i] != '-'
            && expression[i] != '*' && expression[i] != '/' && expression[i] != '%' && expression[i] != '^'
            && expression[i] != '(' && expression[i] != ')')
            return 0;
    }

    //if first or last character is an (invalid) operator
    if (expression[0] == '+' || expression[0] == '-' || expression[0] == '*' || expression[0] == '/'
        || expression[0] == '%' || expression[0] == '^' || expression[0] == ')')
        return 0;
    if(expression[size-1] == '+' || expression[size-1] == '-' || expression[size-1] == '*'
        || expression[size-1] == '/' || expression[size-1] == '%' || expression[size-1] == '^'
        || expression[size-1] == '(')
        return 0;

    //if character before ) or after ( is invalid operator
    //or if character after an operator is an invalid operator
   for (int i = 0; expression[i] != '\0'; i++)
    {
       //if operand followed by (
       if ((expression[i] == '0' || expression[i] == '1' || expression[i] == '2' || expression[i] == '3'
           || expression[i] == '4' || expression[i] == '5' || expression[i] == '6' || expression[i] == '7'
           || expression[i] == '8' || expression[i] == '9') && expression[i + 1] == '(')
           return 0;

        // ( followed by an operator
        if (expression[i] == '(' && (expression[i + 1] == '+' || expression[i + 1] == '-' || expression[i + 1] == '*'
            || expression[i + 1] == '/' || expression[i + 1] == '%' || expression[i + 1] == '^'
            || expression[i + 1] == ')'))
            return 0;
        // operator followed by )
        if ((expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/'
            || expression[i] == '%' || expression[i] == '^') && expression[i + 1] == ')')
            return 0;
        // ) followed by (
        if (expression[i] == ')' && expression[i + 1] == '(')
            return 0;
        //-----------------------------------------------
        //operator cannot be followed by another operator
        
        //+ followed by any operator
        else if (expression[i] == '+' && (expression[i + 1] == '+' || expression[i + 1] == '-'
            || expression[i + 1] == '*' || expression[i + 1] == '/' || expression[i + 1] == '%'
            || expression[i + 1] == '^'))
            return 0;

        //* followed by any operator
        else if (expression[i] == '*' && (expression[i + 1] == '+' || expression[i + 1] == '-'
            || expression[i + 1] == '*' || expression[i + 1] == '/' || expression[i + 1] == '%'
            || expression[i + 1] == '^'))
            return 0;

        // / followed by any operator
        else if (expression[i] == '/' && (expression[i + 1] == '+' || expression[i + 1] == '-'
            || expression[i + 1] == '*' || expression[i + 1] == '/' || expression[i + 1] == '%'
            || expression[i + 1] == '^'))
            return 0;

        //% followed by any operator
        else if (expression[i] == '%' && (expression[i + 1] == '+' || expression[i + 1] == '-'
            || expression[i + 1] == '*' || expression[i + 1] == '/' || expression[i + 1] == '%'
            || expression[i + 1] == '^'))
            return 0;

        //^ followed by any operator
        else if (expression[i] == '^' && (expression[i + 1] == '+' || expression[i + 1] == '-'
            || expression[i + 1] == '*' || expression[i + 1] == '/' || expression[i + 1] == '%'
            || expression[i + 1] == '^'))
            return 0;
    }

    //check if each opening ( has a closing )  {i.e. 7+5) * (8-9 is not valid }
    //and if there are no extra ')'
    bool bracketFound = true;
    int noOfOpening = 0 , noOfClosing = 0;
    for (int i = 0; expression[i] != '\0'; i++)
    {
        if (expression[i] == '(')
        {
            bracketFound = false;
            noOfOpening++;
            for (int j = i + 1; expression[j] != '\0'; j++)
            {
                if (expression[j] == ')')
                {
                    bracketFound = true;
                    break;
                }
            }
        }
        if (expression[i] == ')')
            noOfClosing++;
    }
    if (!bracketFound || noOfOpening != noOfClosing)
        return 0;

    //expression is valid if all above conditions not executed
    return 1;
}

bool PrecedenceCheck(char op1, char op2) { //returns true when precedence of op1 is higher than or equal to op2
    // Highest: % , ^*/ , Lowest: +-

    //False Conditions:-

    // Prec( '(' , operator ) & Prec( operator, '(' ) = False
    if (op1 == '(' || op2 == '(')
        return 0;

    //first level
    if (op2 == '%') //% has highest precedence, op1 cannot be higher
        return 0;
    //second & third levels
    else if ((op2 == '^' || op2 == '/' || op2 == '*') && (op1 == '+' || op1 == '-'))
        return 0;

    //return true if above conditions not executed
    return 1;
}
char* Postfix(char expression[]) {
    char* temp = new char[100]; //declared dynamically to return at end of function
    int index = 0; // to traverse through temp char array (that contains postfix expression)
    Stack<char> stack;
    char tempChar;

    for (int i = 0; expression[i] != '\0'; i++) //traverse through infix expression
    {
        //if operand, add to postfix
        if (expression[i] == '0' || expression[i] == '1' || expression[i] == '2' || expression[i] == '3'
            || expression[i] == '4' || expression[i] == '5' || expression[i] == '6' || expression[i] == '7'
            || expression[i] == '8' || expression[i] == '9')
        {
            temp[index++] = expression[i]; //stores in temp[index], then increments index for next character

            //add space between two operands
            if (expression[i + 1] == ')' || expression[i + 1] == '%' || expression[i + 1] == '^'
                || expression[i + 1] == '*' || expression[i + 1] == '/' || expression[i + 1] == '+'
                || expression[i + 1] == '-') //if next char is not another number
                temp[index++] = ' ';
        }
        else //if operator
        {
            while (!stack.isEmpty() && PrecedenceCheck(stack.peek(), expression[i]))
            {   //if same or higher precedence operator already on stack, remove & add to postfix
                tempChar = stack.Pop();
                if (tempChar == '('); //discard (
                else
                { //add space between operators as well, for output
                    temp[index++] = tempChar;
                    temp[index++] = ' ';
                }
            }

            //if nothing in stack, or operator is not ) => push operator onto stack.
            if (stack.isEmpty() || expression[i] != ')')
                stack.Push(expression[i]);
            else
                stack.Pop(); //discard )
        }
    }

    //add remaining operators to postfix
    while (!stack.isEmpty())
    {
        tempChar = stack.Pop();
        temp[index++] = ' ';
        temp[index++] = tempChar;
    }

    temp[index] = '\0'; //temp char array is completed. terminating character added to end.

    return temp;
}

char* ReverseString(char str[])
{
    int size = 0;
    char* temp = new char[100];

    for (int i = 0; str[i] != '\0'; i++)
    {
        size++;
    }

    int index = size - 1; //start from last element of passed charr array

    for (int i = 0; i < size; i++)
    {
        temp[i] = str[index]; //store each element of passed array into new array
        index--;
    }

    temp[size] = '\0'; //terminating character added

    return temp;
}
void Prefix(char expression[])
{   
    //1. Reverse the string
     char* temp = ReverseString(expression);

    // -> Swap ( and ) in reversed string
    for (int i = 0; temp[i] != '\0'; i++)
    {
        if (temp[i] == '(')
            temp[i] = ')';
        else if (temp[i] == ')')
            temp[i] = '(';
    }

    //2. Convert this string into postfix
    temp = Postfix(temp);

    //3. Reverse the string again
    temp = ReverseString(temp);

    //output the Prefix expression
    cout << temp;
}

double Evaluate(char expression[]) {
    char* temp = Postfix(expression); //postfix expression will be evaluated
    Stack<double> stack;
    int n = 0, tempN = 0;
    double ans = 1;

    for (int i = 0; temp[i] != '\0'; i++)
    {
        //if operand
        if (temp[i] == '0' || temp[i] == '1' || temp[i] == '2' || temp[i] == '3'
            || temp[i] == '4' || temp[i] == '5' || temp[i] == '6' || temp[i] == '7'
            || temp[i] == '8' || temp[i] == '9')
        {
            stack.Push(static_cast<double>(temp[i]) - 48);

            //to push one operand as one element on stack
            while (temp[i + 1] != ' ' && temp[i + 1] != '+' && temp[i + 1] != '-' && temp[i + 1] != '*'
                && temp[i + 1] != '/' && temp[i + 1] != '%' && temp[i + 1] != '^' && temp[i + 1] != ')')
            //=> until next element is an operand:
            {
                n = static_cast<int>(stack.Pop());
                n *= 10;
                tempN = static_cast<int>(temp[i + 1]) - 48;
                n += tempN;
                stack.Push(n);
                i++; //skip next element of char array, as it is pushed on stack
            }
        }
        else if (temp[i] == '+' || temp[i] == '-' || temp[i] == '*' || temp[i] == '/' || temp[i] == '%'
            || temp[i] == '^') //if operator found
        {
            ans = 1.0;
            double operand1, operand2;

            // operand2 (operator) operand1
            operand2 = stack.Pop();
            operand1 = stack.Pop();

            switch (temp[i]) //implement case according to operator
            {
            case '%':
            {
                // % only for integer values
                ans = static_cast<int>(operand1) % static_cast<int>(operand2);
                break;
            }
            case '*':
            {
                ans = operand1 * operand2;
                break;
            }
            case '/':
            {
                ans = operand1 / operand2;
                break;
            }
            case '^': //operand1 ^ operand2
            {
                // m^n = m * m * ... n times
                for (int i = 0; i < operand2; i++)
                {
                    ans *= operand1;
                }
                break;
            }
            case '+':
            {
                ans = operand1 + operand2;
                break;
            }
            case '-':
            {
                ans = operand1 - operand2;
                break;
            }
            }
            stack.Push(ans); //push evaluated number back onto stack, and continue with while loop
        }
    }

    //final evaluated answer now on stack.
    return stack.Pop();
}

int main()
{
    char expression[100]; //declare char array of size 100
    
    cout << "(Valid expression: no spaces, no operators followed by operators, only () brackets, used correctly.)" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
    cout << "Enter an infix expression with operands and operators only (+,-,*,/,%,^) (Enter to stop):" << endl;
    cin.getline(expression, 100); //take expression as input till newline or 100 characters entered

    cout << endl << "Input from the user = ";
    for (int i = 0; expression[i] != '\0'; i++)
    {
        cout << expression[i];
    }

    cout << endl << "Check Validity: ";
    if (!CheckValidity(expression)) //if invalid expression, terminate the program
    {
        cout << "Invalid expression entered. Program terminated." << endl;
        return 0;
    }
    else //expression is valid, further processing can be done
    {
        //declare expression as valid
        cout << "Your expression is valid" << endl << endl;
        
        //change notation, output
        cout << "Prefix: ";
        Prefix(expression);
        cout << endl;

        cout << "Postfix: " << Postfix(expression) << endl;

        cout << "Result: " << Evaluate(expression) << endl;
    }

    return 0;
}
