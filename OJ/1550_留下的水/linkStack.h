#ifndef linkStack_
#define linkStack_
#include "stack.h"

template <class elemType>
class linkStack:public stack<elemType>
{
private:
    struct node
    {
        elemType data;
        node *next;
        node (const elemType &x, node *N=NULL)
        {
            data = x;
            next = N;
        }
        node():next(NULL) {}
        ~node() {}
    };
    node *top;
public:
    linkStack();
    ~linkStack();
    bool isEmpty() const;
    elemType getTop() const;
    elemType pop();
    void push(const elemType &x);
};
#endif
