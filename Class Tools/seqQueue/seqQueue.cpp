#include <iostream>
#include "seqQueue.h"
using namespace std;

template <class elemType>
void seqQueue<elemType>::doubleSpace()
{
    elemType *tmp=elem;
    elem = new elemType[2*maxSize];
    for (int i=1; i<maxSize; ++i)
        elem[i] = tmp[(front+i)%maxSize];
    front = 0;
    rear = maxSize-1;
    maxSize*=2;
    delete tmp;
}

template <class elemType>
void seqQueue<elemType>::enQueue(const elemType &x)
{
    if ((rear+1)%maxSize==front)
        doubleSpace();
    rear = (rear+1)%maxSize;
    elem[rear] = x;
}

template <class elemType>
elemType seqQueue<elemType>::deQueue()
{
    front = (front+1)%maxSize;
    return elem[front];
}
