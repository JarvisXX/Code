#include <iostream>
using namespace std;

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

template <class Type>
void priorityQueue<Type>::doubleSpace()
{
    Type *tmp=array;
    array = new Type[2*maxSize];
    for (int i=1; i<maxSize; ++i)
        array[i] = tmp[i];
    maxSize*=2;
    delete [] tmp;
}

template <class Type>
void priorityQueue<Type>::buildHeap()
{
    for (int i=currentSize/2; i>=1; --i)
        percolateDown(i);
}

template <class Type>
void priorityQueue<Type>::percolateDown(int hole)
{
    int child;
    Type tmp=array[hole];
    while (hole*2<=currentSize)
    {
        child = hole*2;
        if (child!=currentSize && array[child+1]<array[child])
            ++child;
        if (array[child]<tmp)
            array[hole] = array[child];
        else
            break;
        hole = child;
    }
    array[hole] = tmp;
}

template <class Type>
priorityQueue<Type>::priorityQueue(int capacity)
{
    array = new Type[capacity];
    maxSize = capacity;
    currentSize = 0;
}

template <class Type>
priorityQueue<Type>::priorityQueue(const Type *data, int size):maxSize(size+10), currentSize(size)
{
    array = new Type[maxSize];
    for (int i=0; i<size; ++i)
        array[i+1] = data[i];
    buildHeap();
}

template <class Type>
bool priorityQueue<Type>::isEmpty() const
{
    return currentSize==0;
}

template <class Type>
void priorityQueue<Type>::enQueue(const Type &x)
{
    if (currentSize==maxSize-1)
        doubleSpace();
    int hole=++currentSize;
    for (; hole>1 && x<array[hole/2]; hole/=2)
        array[hole] = array[hole/2];
    array[hole] = x;
}

template <class Type>
Type priorityQueue<Type>::deQueue()
{
    Type minItem;
    minItem = array[1];
    array[1] = array[currentSize--];
    percolateDown(1);
    return minItem;
}

template <class Type>
Type priorityQueue<Type>::getHead() const
{
    return array[1];
}

int main()
{
    int M;
    cin >> M;
    priorityQueue<int> pQueue(M);

    string op;
    for (int i=0; i<M; ++i)
    {
        cin >> op;
        if (op=="insert")
        {
            int a;
            cin >> a;
            pQueue.enQueue(a);
        }
        else if (op=="delete")
            pQueue.deQueue();
        else if (op=="min")
            cout << pQueue.getHead() <<endl;
    }
}

