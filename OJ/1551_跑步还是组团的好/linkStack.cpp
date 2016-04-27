#include <iostream>
#include <cstdlib>
#include "linkStack.h"
using namespace std;

template <class elemType>
linkStack<elemType>::linkStack()
{
    top = NULL;
}

template <class elemType>
linkStack<elemType>::~linkStack()
{
    node *tmp;
    while (top!=NULL)
    {
        tmp = top;
        top = top->next;
        delete tmp;
    }
}

template <class elemType>
bool linkStack<elemType>::isEmpty() const
{
    return top==NULL;
}

template <class elemType>
elemType linkStack<elemType>::getTop() const
{
    if (isEmpty())
    {
        cout << "The stack is empty.";
        exit(0);
    }
    return top->data;
}

template <class elemType>
elemType linkStack<elemType>::pop()
{
    if (isEmpty())
    {
        cout << "The stack is empty.";
        exit(0);
    }
    node *tmp=top;
    elemType x=top->data;
    top = top->next;
    delete tmp;
    return x;
}

template <class elemType>
void linkStack<elemType>::push(const elemType &x)
{
    node *tmp=new node(x, top);
    top = tmp;
}
