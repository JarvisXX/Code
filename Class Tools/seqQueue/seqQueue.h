#ifndef seqQueue_
#define seqQueue_
#include "queue.h"

template <class elemType>
class seqQueue:public queue<elemType>
{
private:
    elemType *elem;
    int maxSize;
    int front, rear;
    void doubleSpace();
public:
    seqQueue(int size=10)
    {
        elem = new elemType[size];
        maxSize = size;
        front = rear = 0;
    }
    ~seqQueue() {delete [] elem;}
    bool isEmpty() {return front==rear;}
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead()
    {
        return elem[(front+1)%maxSize];
    }
};
#endif
