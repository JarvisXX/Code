#include <iostream>
using namespace std;

template <class Type>
class priorityQueue
{
private:
    int currentSize;
    int maxSize;

    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);
public:
    Type *array;

    priorityQueue(int capacity=100);
    priorityQueue(const Type *data, int size);
    ~priorityQueue() {delete [] array;}
    int getSize() const;
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
int priorityQueue<Type>::getSize() const
{
    return currentSize;
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
            int x;
            cin >> x;
            pQueue.enQueue(x);
        }
        else if (op=="find")
        {
            int x;
            cin >> x;
            int pos=0;
            for (int i=1; i<=pQueue.getSize(); ++i)
                if (pQueue.array[i]>x && (pos==0 || pQueue.array[i]<pQueue.array[pos]))
                    pos = i;
            cout << pos <<endl;
        }
        else if (op=="decrease")
        {
            int i, v;
            cin >> i >> v;
            int x=pQueue.array[i]-v;
            int hole=i;
            for (; hole>1 && x<pQueue.array[hole/2]; hole/=2)
                pQueue.array[hole] = pQueue.array[hole/2];
            pQueue.array[hole] = x;
        }
    }
}
