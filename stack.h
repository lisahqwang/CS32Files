#ifndef STACK_INCLUDED
#define STACK_INCLUDED

#include <iostream>

using namespace std;

class Stack
{
    public:
        Stack(); // default constructor
        Stack(const Stack& other); // copy constructor
        Stack& operator=(const Stack& other); // assignment
        void swap(Stack& other); // for use with assignment
        ~Stack(); // destructor
        void push(int val); // add val to top of stack
        void pop(); // remove top
        void display();
    private:
        struct Node
        {
            int data;
            Node* next;
        };
        Node* top;
};

Stack::Stack() : top(nullptr) {}

void Stack::push(int val)
{
    Node* new_top = new Node;
    new_top->next = top;
    new_top->data = val;
    top = new_top;
}

// if empty do nothing, otherwise remove top element
void Stack::pop()
{
    if(top != nullptr)
    {
        Node* new_top = top->next;
        delete top;
        top = new_top;
    }
}

// print contents of the stack from top to bottom
void Stack::display()
{
    for(Node* curr = top; curr != nullptr; curr = curr->next)
        cout << curr->data << endl;
}

void Stack::swap(Stack& other)
{
    Node* temp = top;
    top = other.top;
    other.top = temp;
}

Stack& Stack::operator=(const Stack& other)
{
    if(this != &other)
    {
        Stack temp(other);
        swap(temp);
    }
    return *this;
}

Stack::~Stack()
{
    Node* curr = top;
    while(curr != nullptr)
    {
        Node* to_delete = curr;
        curr = curr->next;
        delete to_delete;
    }
}

// note: top == nullptr <===> stack is empty
Stack::Stack(const Stack& other)
{
    if (other.top != nullptr)
    {
        // copy top node
        top = new Node;
        top->data = other.top->data;
        top->next = nullptr; // always initialize
        
        // create curr pointers
        Node* this_curr = top;
        Node* other_curr = other.top;
        
        // while we're not at the last node, copy the next node
        while(other_curr->next != nullptr)
        {
            // copy next
            Node* new_node = new Node;
            new_node->data = other_curr->next->data;
            new_node->next = nullptr;
            this_curr->next = new_node;
            
            // increment
            other_curr = other_curr->next;
            this_curr = this_curr->next;
        }
    }
    else
    {
        top = nullptr;
    }
}



#endif
