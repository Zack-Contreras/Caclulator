/****************
Zackary Contrears
ZCC190000
****************/
#ifndef STACK_H
#define STACK_H
#include "node.h"
#include <iostream>

class Stack
{
    public:
        //Accessors
        Node* getHead(){return head;}
        //Mutators
        void setHead(Node *n){head = n;}
        //Constructors
        Stack();
        Stack(Node);
        //Copy Constructor
        Stack(Stack&);
        //Destructor
        ~Stack();
        //Overloaded Operator
        friend std::ostream& operator<<(std::ostream&, const Stack&);
        friend void operator<<(Stack&, Node*&);
        friend void operator>>(Stack&, Node*&);
        void destroyStack(Node*);

    protected:

    private:
        Node *head = nullptr;

};

#endif // STACK_H
