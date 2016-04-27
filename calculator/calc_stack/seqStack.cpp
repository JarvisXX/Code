#include <iostream>
#include <cstdlib>
#include "seqStack.h"
using namespace std;

template <class elemType>
seqStack<elemType>::seqStack(int initSize)
{
    elem = new elemType[initSize];
    maxSize = initSize;
    top = -1;
}

template <class elemType>
bool seqStack<elemType>::isEmpty() const
{
    return top==-1;
}

template <class elemType>
elemType seqStack<elemType>::getTop() const
{
    if (isEmpty())
    {
        cout << "The stack is empty.";
        exit(0);
    }
    return elem[top];
}

template <class elemType>
elemType seqStack<elemType>::pop()
{
    if (isEmpty())
    {
        cout << "The stack is empty.";
        exit(0);
    }
    return elem[top--];
}

template <class elemType>
void seqStack<elemType>::push(const elemType &x)
{
    if (top==maxSize-1) doubleSpace();
    elem[++top] = x;
}

template <class elemType>
void seqStack<elemType>::doubleSpace()
{
    elemType *tmp=elem;
    elem = new elemType[2*maxSize];
    for (int i=0; i<maxSize; ++i) elem[i]=tmp[i];
    maxSize *= 2;
    delete [] tmp;
}
