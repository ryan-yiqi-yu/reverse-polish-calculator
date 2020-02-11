
#include<iostream>
#include<string>
#include<sstream>
using namespace std;

class revpolish{
private:
    struct node { //linked nodes of the stack
        double data;
        node * next;
    };
    node * topOfstack = NULL; //initialized top of stack pointer
    int elementsInstack = 0; //this is a counter to keep track of how many nodes are in the stack
public:
    
    void push(double NewValue){ //this is a push method to add a node onto the stack
        node *NewNode = new node;
        NewNode->data = NewValue;
        NewNode->next = topOfstack;
        topOfstack = NewNode;
        elementsInstack++; //pushing a node onto top of the stack increases the node count
    }
    
    double pop(){ //pop method to remove and return the top value off the stack
        double x = topOfstack->data;
        topOfstack = topOfstack->next;
        elementsInstack--; //popping a node decreases the node count
        return x;
    }

    void solution(){ //this method should bring everything together(the user input, the errors, and the calculations)
        string expression; //declared string which will later, at line 41, be used to hold the user input
        double test; //this test variable is not significant, it's used at line 43 to count how many operands were entered
        while (true){ //until this while loop is broken out of, it will continue to ask the user for an input
            cout<<"Enter reverse polish expression ending with an '=', '0' to stop:"<<endl;
            getline(cin, expression); //the reverse polish expression the user entered is now in "expression" variable declared earlier on line 36
            stringstream ss(expression); //the reverse polish expression will now be loaded onto a stringstream "ss"
            int count = 0; //same for count variable, used at line 44 to increment how many operands there are
            while (ss>>test){ //since "test" is type double, every double that the user entered will be counted by this while statement, other characters are not counted
                count++; //counting total operands
            }
            if (count == 1 && test == 0){ //this if-statement verifies that there has only been one operand entered AND the only operand had value 0
                cout<<"Execution stopped"<<endl<<endl<<endl; //since entering 0 and a new line will end the program, if this if-statement is true, it breaks out the while statement and ends the loop, ending the program
                break;
            }
            else{ //this else-statement will execute if the user did not enter 0 and a new line
                try { //this try-suite will execute the calculation method which may potentially throw 3 different errors
                    calculation(expression); //the expression variable which contains the user input will be passed to the calculation method
                } catch (const char* n) { //catching a potential error that is thrown from calculation method
                    cout<<n<<endl<<endl; //printing the error message thrown from the calculation method
                    const int size = elementsInstack; //declaring the size variable in order to clear the stack
                    for (int i = 0; i < size; i++){ //for-statement clears all the nodes in the stack after an error occurs, preparing the stack to be used again
                        pop(); //removing node
                    }
                }
                
            }
        }
        }
    void calculation(string x){ //this is the calculation method which will accept a string variable that contains the user's input
        string iterate; //"iterate" variable will be used to iterate every each individual operand/operator in the input
        stringstream s(x); //putting the user inputted string, the reverse polish expression, into a stringstream "s"
        double operand, num1, num2; //variables that will be used to push onto the stack
        while (s>>iterate){ //for every element in the user input, the following code in the while-suite will execute and do somethign with it. The element is referred to as "iterate"
            if (stringstream (iterate) >> operand){ //this if-statement determines if the element is an operand, if so, it is pushed onto the stack
                push(operand); //pushes operand onto stack
            }
            else{ //this else-suite is executed iff the element in the user input is NOT an operand, therefore it must be an operator
                char operatorr;
                stringstream (iterate) >> operatorr; //the element is loaded into a char variable, "operatorr"
                if (elementsInstack < 2 && operatorr != '='){ //if the reverse polish expression has less then 2 operands before an operator, it means it has too many operators, therefore, this if-suite will throw an error
                    throw "Error, too many operators"; //throwing the error
                }
                else{ //this else-suite is executed if the operator in question has at least 2 operands preceeding it
                    switch(operatorr){ //this switch-statement will determine what the operator sign is and execute specific code depending on the operator
                        case('+'): //in-case the operator is '+'
                            num2 = pop();
                            num1 = pop(); //pops the last two values on top of stack
                            push(num1+num2); //pushes the sum of the two values onto stack
                            break;
                        case('-'): //in-case the operator is '-'
                            num2 = pop();
                            num1 = pop(); //pops the last two values on top of stack
                            push(num1-num2); //pushes the difference of the two values onto stack
                            break;
                        case('*'): //in-case the operator is '*'
                            num2 = pop();
                            num1 = pop(); //pops the last two values on top of stack
                            push(num1*num2); //pushes the product of the two values onto stack
                            break;
                        case('/'): //in-case the operator is '/'
                            num2 = pop();
                            num1 = pop(); //pops the last two values on top of stack
                            if (num2 == 0){ //checks for whether the divisor is 0 since dividing by 0 is illegal
                                throw "Error, division by zero"; //if divisor is 0, appropriate error is thrown
                                break;
                            }
                            else{
                                push(num1/num2); //pushes the quotient of the two values onto stack, iff the divisor is not 0
                                break;
                            }
                            
                        case('='): //in-case the operator is '='
                            if (elementsInstack > 1){ // if the expression was entered correctly, the stack should only have 1 operand left at the = sign, therefore, this if-statement checks for whether too many operands were incorrectly entered
                                throw "Error, too many operands"; //if there are too many operands, appropriate error is thrown
                                
                            }
                            else{ //if the expression was correctly entered, the following else-suite will execute
                                cout<<pop()<<endl<<endl; //pops and outputs the final answer of the reverse polish expression
                            }
                            break;
                            
                    }
                }
                
            }
        
    }
        
    }
    
    };

int main(){
    revpolish test; //creating reverse polish object
    test.solution(); //running the solution method which includes all the code(the user input, the errors, the calculations, and the output)
}



/*
 OUTPUT(the following from line 139 to 176 is the output of my program):
 
 
 Enter reverse polish expression ending with an '=', '0' to stop:
 10 15 + =
 25

 Enter reverse polish expression ending with an '=', '0' to stop:
 10 15 - =
 -5

 Enter reverse polish expression ending with an '=', '0' to stop:
 2.5 3.5 + =
 6

 Enter reverse polish expression ending with an '=', '0' to stop:
 10 0 / =
 Error, division by zero

 Enter reverse polish expression ending with an '=', '0' to stop:
 10 20 * / =
 Error, too many operators

 Enter reverse polish expression ending with an '=', '0' to stop:
 12 20 30 / =
 Error, too many operands

 Enter reverse polish expression ending with an '=', '0' to stop:
 -10 -30 - =
 20

 Enter reverse polish expression ending with an '=', '0' to stop:
 100 10 50 25 / * - -2 / =
 -40

 Enter reverse polish expression ending with an '=', '0' to stop:
 0
 Execution stopped


 Program ended with exit code: 0
 */

//FINAL EDIT
