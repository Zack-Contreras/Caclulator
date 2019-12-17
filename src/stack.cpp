/****************
Zackary Contrears
ZCC190000
****************/
#include "stack.h"
#include <iostream>

Stack::Stack()
{
    head = nullptr;
}

Stack::Stack(Node h) {
    Node* app = new Node;
    app->setOperand(h.getOperand());
    app->setOperator(h.getOperator());
    if (!head) {
        head = app;
    }
}

/***COPY CONSTRUCTOR***/
Stack::Stack(Stack& s) {
    Node* h = s.getHead();
    while (h != nullptr) {
        Node* app = new Node;
        app->setOperand(h->getOperand());
        app->setOperator(h->getOperator());
        if (!head) {
           head = app;
        }
        else {
            Node* trav = head;
            while (trav->getNext() != nullptr) {
                trav = trav->getNext();
            }
            trav->setNext(app);
        }
        h = h->getNext();
    }
}

/***RECURSIVE DESTRUCTOR FUNCTION**/
void Stack::destroyStack(Node* head) {
    if (head != nullptr) {
        Node* hold = nullptr;
        hold = head;
        head = head->getNext();
        delete hold;
        destroyStack(head);
    }
    else {
        return;
    }
}
Stack::~Stack() {
    destroyStack(head);
}

/**OVERLOAD << FOR OUTPUT**/
std::ostream& operator<<(std::ostream& out, const Stack& obj) {
    //traversal pointer used in for loop
    Node* trav;
    bool first = true;
    //Print out each node in stack
    for (trav = obj.head; trav != nullptr; trav = trav->getNext()) {
        //format for first printed node
        if (first) {
            first = false;
            if (trav->getOperator() != ' ') {
                out << trav->getOperator();
            } else {
                out << trav->getOperand();
            }
        }
        //format for printed nodes after first
        else {
            if (trav->getOperator() != ' ') {
                out << ", " << trav->getOperator();
            } else {
                out << ", " << trav->getOperand();
            }
        }
    }
    return out;
}

/**OVERLOAD << FOR PUSH**/
void operator<<(Stack& obj, Node* &node) {
    //when stack is NOT empty
    if (obj.getHead() != nullptr) {
        node->setNext(obj.getHead());
        obj.setHead(node);
    }
    //when stack IS empty
    else {
        obj.setHead(node);
    }
}

/**OVERLOAD >> FOR POP**/
void operator>>(Stack& obj, Node* &node){
    //remove first item in stack IF stack is NOT empty
    if (obj.head != nullptr) {
        //assign first item in stack to parameter
        node = obj.head;
        obj.setHead(obj.head->getNext());
    }
    //OTHERWISE do nothing
    else {
        node = nullptr;
    }
}


