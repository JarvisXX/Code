#ifndef seqStack_
#define seqStack_
#include "stack.h"

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
#endif
