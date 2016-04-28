#include <iostream>
#include <cstdlib>
#include <cstring>
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
    char ch;
    int num=0;
    int N=0;
    int root=0;
    linkStack<int> stack;
    priorityQueue<int> tree;
    int father[100010];
    int neighbor[100010];

    memset(father, 0, sizeof(father));
    memset(neighbor, 0, sizeof(neighbor));
    while (cin>>ch)
    {
        if (ch==' ')
            continue;
        else if (ch=='(')
        {
            if (num!=0)
            {
                stack.push(num);
                if (root==0)
                    root = num;
                N = (N>num?N:num);
                num = 0;
            }
        }
        else if (ch==')')
        {
            if (num!=0)
            {
                father[num] = stack.getTop();
                ++neighbor[num];
                ++neighbor[stack.getTop()];
                N = (N>num?N:num);
                num = 0;
            }
            else
            {
                int leaf=stack.pop();
                if (!stack.isEmpty())
                {
                    father[leaf] = stack.getTop();
                    ++neighbor[leaf];
                    ++neighbor[stack.getTop()];
                }
            }
        }
        else
            num = num*10+ch-'0';
    }

    for (int i=1; i<=N; ++i)
        if (neighbor[i]==1)
            tree.enQueue(i);

    for (int i=0; i<N-1; ++i)
    {
        int out=tree.deQueue();
        if (out==root)
        {
            for (int j=1; j<=N; ++j)
            {
                if (father[j]==root && neighbor[j]!=0)
                {
                    cout << j <<' ';
                    --neighbor[root];
                    --neighbor[j];
                    if (neighbor[j]==1)
                        tree.enQueue(j);
                    root = j;
                    break;
                }
            }
        }
        else
        {
            cout << father[out] <<' ';
            --neighbor[out];
            --neighbor[father[out]];
            if (neighbor[father[out]]==1)
                tree.enQueue(father[out]);
        }
    }
}
