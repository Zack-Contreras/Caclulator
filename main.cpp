/****************
Zackary Contrears
ZCC190000
****************/
#include "node.h"
#include "stack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iomanip>
#include <math.h>

using namespace std;

int checkPrior(char op);
void convertPostfix(string expression, string &postfix);
void calculateExpression(string postfix, Stack &stk2);

int main()
{
    string input, expression;
    cin >> input;
    ifstream inFile(input);
    //Loop through input file
    while (getline(inFile, expression)) {
        //When an expression is found
        if (expression != "") {
            string postfix = "";
            //Call function to convert expression to postfix
            convertPostfix(expression, postfix);
            //Call function to calculate value from postfix and print to console
            Stack stk2;
            calculateExpression(postfix, stk2);
        }
    }
    inFile.close();
    return 0;
}

//RETURN INT BASED ON PRIORITY LEVEL OF OPERATOR//
int checkPrior(char op) {
    if (op == '^') {
        return 3;
    }
    else if(op == '*' || op == '/') {
        return 2;
    }
    else if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '(' || op == ')') {
        return 0;
    }
    return -1;
}

//CONVERTS PREFIX TO POSTFIX NOTATION//
//TAKES STRING CONTAINING PREFIX EXPRESSION & EMPTY STRING TO STORE POSTFIX//
void convertPostfix(string expression, string &postfix) {
    Stack stk;
    //check each character in the string
    for (size_t i = 0; i<expression.length(); i++) {
        //when the character is a number or decimal, append to postfix
        if (isdigit(expression[i]) || expression[i] == '.') {
            //Append to postfix
            postfix += expression[i];
        }
        //when parenthesis is hit
        else if (expression[i] == '(' || expression[i] == ')') {
            //push left parenthesis to stack
            if (expression[i] == '(') {
                    Node* add = new Node;
                    add->setOperator(expression[i]);
                    stk << add;
            }
            //Pop and append to stack until left '(' is hit
            else if (expression[i] == ')') {
                    Node* d = new Node;
                    while (stk.getHead()->getOperator() != '(') {
                        stk >> d;
                        postfix += ' ';
                        postfix += d->getOperator();
                        delete d;
                    }
                    d = nullptr;
                    //pop left parenthesis but do NOT append to postfix
                    Node* test = new Node;
                    stk >> test;
            }
        }
        //when operator is hit
        else if (checkPrior(expression[i]) > 0) {
            Node* del = new Node;
            del = nullptr;
            postfix += " ";
            Node* ptr = new Node;
            ptr->setOperator(expression[i]);
            //loop through stack and check priority to pop or push
            if (stk.getHead() == nullptr) {
                //push operator onto stack
                stk << ptr;
            }
            else {
                Node* trav = nullptr;
                trav = stk.getHead();
                //loop and delete lower priority while appending to postfix
                while (trav != nullptr && checkPrior(expression[i]) <= checkPrior(trav->getOperator())){
                    //delete allocated memory when popped
                    if (del)
                        delete del;
                    //compare priority of operators and pop/append if necessary
                        stk >> del;
                        //append to postfix
                        postfix += del->getOperator();
                        postfix += ' ';
                        trav = trav->getNext();
                }
                //push operator onto stack
                stk << ptr;
            }
        }
    }
    //append rest of stack to postfix
    while (stk.getHead() != nullptr) {
        Node* hold = new Node;
        stk >> hold;
        postfix += ' ';
        postfix += hold->getOperator();
        delete hold;
    }
}

//CALCULATES AN ANSWER FROM POSTFIX NOTATION//
//TAKES STRING CONTAINING POSTFIX EXPRESSION AND EMPTY STACK TO USE//
void calculateExpression(string postfix, Stack &stk2) {
    string holder;
    for (size_t i = 0; i<postfix.length(); i++){
        //create value for node when digit or . it read
        if (isdigit(postfix[i]) || postfix[i] == '.') {
            holder += postfix[i];
        }
        //add value to node when a space is hit
        else if (postfix[i] == ' ') {
            //add operand to list
            if (holder != "") {
                Node* add = new Node;
                add->setOperand(stof(holder));
                stk2 << add;
            }
            //reset holder variable for next value
            holder = "";
        }
        //operator hit
        else if (checkPrior(postfix[i]) > 0){
                Node* h1 = new Node;
                Node* h2 = new Node;
                float calc = 0;
                stk2 >> h1;
                stk2 >> h2;
                //calculate expression using 2 operand from stack
                switch (postfix[i]) {
                    case '+': calc = h1->getOperand() + h2->getOperand();
                                break;
                    case '-': calc = h2->getOperand() - h1->getOperand();
                                break;
                    case '*': calc = h1->getOperand() * h2->getOperand();
                                break;
                    case '/': calc = h2->getOperand() / h1->getOperand();
                                break;
                    case '^': calc = pow(h2->getOperand(), h1->getOperand());
                                break;
                    default: calc = h1->getOperand() + h2->getOperand();
                }
                Node* calculated = new Node;
                calculated->setOperand(calc);
                //push calculate expression onto stack
                stk2 << calculated;
                delete h1;
                delete h2;
        }
    }
    //pop final val in stack to get answer
    Node* answer = new Node;
    stk2 >> answer;
    cout << fixed << showpoint << setprecision(3) << postfix << "\t" << answer->getOperand() << "\n";
    delete answer;
}
