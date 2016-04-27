#include <iostream>
using namespace std;

template <class elemType>
class queue
{
public:
    virtual bool isEmpty() = 0;
    virtual void enQueue(const elemType &x) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead() = 0;
    virtual ~queue() {}
};

template <class elemType>
class linkQueue:public queue<elemType>
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
    node *front, *rear;
public:
    linkQueue() {front = rear = NULL;}
    ~linkQueue();
    bool isEmpty() {return front==NULL;}
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead() {return front->data;}
};

template <class elemType>
linkQueue<elemType>::~linkQueue()
{
    node *tmp;
    while (front!=NULL)
    {
        tmp = front;
        front = front->next;
        delete tmp;
    }
}

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
    if (rear==NULL)
        front = rear = new node(x);
    else
    {
        rear->next = new node(x);
        rear = rear->next;
    }
}

template <class elemType>
elemType linkQueue<elemType>::deQueue()
{
    node *tmp = front;
    elemType value = front->data;
    front = front->next;
    if (front==NULL) rear=NULL;
    delete tmp;
    return value;
}

void OldMethod(int N, int line[], long long &total_time, long long &last_one)
{
    int quo=N/3;
    long long t0=0, t1=0, t2=0;
    switch(N%3)
    {
        case 0:
        {
            for (int i=0; i<N; ++i)
            {
                switch(i%3)
                {
                    case 0: total_time += t0; t0 += line[i]; break;
                    case 1: total_time += t1; t1 += line[i]; break;
                    case 2: total_time += t2; t2 += line[i]; break;
                }
            }
            break;
        }
        case 1:
        {
            for (int i=0; i<N; ++i)
            {
                switch(i%3)
                {
                    case 0: total_time += t0; t0 += line[i]; break;
                    case 1: total_time += t1; t1 += line[i]; break;
                    case 2: total_time += t2; t2 += line[i]; break;
                }
            }
            break;
        }
        case 2:
        {
            for (int i=0; i<N; ++i)
            {
                switch(i%3)
                {
                    case 0: total_time += t0; t0 += line[i]; break;
                    case 1: total_time += t1; t1 += line[i]; break;
                    case 2: total_time += t2; t2 += line[i]; break;
                }
            }
            break;
        }
    }
    last_one = ((t0>t1?t0:t1)>t2?(t0>t1?t0:t1):t2);
}

void NewMethod(int N, linkQueue<int> &que, long long &total_time, long long &last_one)
{
    long long t0=0, t1=0, t2=0;
    while(!que.isEmpty())
    {
        if (t1<=t2)
        {
            if (t0<=t1)
            {
                //-> t0
                total_time += t0;
                t0 += que.deQueue();
            }
            else
            {
                //-> t1
                total_time += t1;
                t1 += que.deQueue();
            }
        }
        else
        {
            if (t0<=t2)
            {
                //-> t0
                total_time += t0;
                t0 += que.deQueue();
            }
            else
            {
                //-> t2
                total_time += t2;
                t2 += que.deQueue();
            }
        }
    }
    last_one = ((t0>t1?t0:t1)>t2?(t0>t1?t0:t1):t2);
}

int main()
{
    int N;
    int line[100010];
    linkQueue<int> que;
    long long total_timeOld=0, last_oneOld=0, total_timeNew=0, last_oneNew=0;
    cin >> N;
    for (int i=0; i<N; ++i)
    {
        int input;
        cin >> input;
        line[i] = input;
        que.enQueue(input);
    }
    OldMethod(N, line, total_timeOld, last_oneOld);
    NewMethod(N, que, total_timeNew, last_oneNew);
    cout << total_timeOld <<' '<< last_oneOld <<endl;
    cout << total_timeNew <<' '<< last_oneNew;
}
