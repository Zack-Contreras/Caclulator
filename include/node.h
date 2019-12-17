/****************
Zackary Contrears
ZCC190000
****************/
#ifndef NODE_H
#define NODE_H


class Node
{
    public:
        //Accessors
        float getOperand() const {return operand;}
        char getOperator() const {return operator_;}
        Node* getNext() const {return next;}
        //Mutators
        void setOperand(float f){operand = f;}
        void setOperator(char o){operator_ = o;}
        void setNext(Node* n){next = n;}
        //Constructors
        Node();
        Node(float f){operand = f;}
        Node(char o){operator_ = o;}
        Node(float f, char o){operand = f; operator_ = o;}

    protected:

    private:
        float operand = 0.00;
        char operator_ = ' ';
        Node* next = nullptr;
};

#endif // NODE_H
