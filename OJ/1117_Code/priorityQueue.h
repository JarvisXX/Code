//priorityQueue.h
#ifndef pQ_
#define pQ_
template <class Type>
class priorityQueue
{
private:
    int currentSize;
    Type *array;
    int maxSize;

    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);
public:
    priorityQueue(int capacity=100);
    priorityQueue(const Type *data, int size);
    ~priorityQueue() {delete [] array;}
    bool isEmpty() const;
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead() const;
};
#endif
