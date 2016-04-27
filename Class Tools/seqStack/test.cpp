#include <iostream>
#include <cstdlib>
using namespace std;

template <class elemType>
class stack
{
public:
    virtual bool isEmpty() const = 0;
    virtual void push(const elemType &x) = 0;
    virtual elemType getTop() const = 0;
    virtual elemType pop() = 0;
    virtual ~stack() {}
};

template <class elemType>
class seqStack:public stack<elemType>
{
private:
    elemType *elem;
    int top;
    int maxSize;
    void doubleSpace();
public:
    seqStack(int initSize=10);
    ~seqStack() {delete [] elem;}
    bool isEmpty() const;
    elemType getTop() const;
    elemType pop();
    void push(const elemType &x);
};

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

