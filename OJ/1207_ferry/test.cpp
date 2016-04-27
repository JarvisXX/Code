#include <iostream>
#include <iomanip>
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

int main()
{
    int N;
    int busNum=0, truNum=0;
    linkQueue<int> bus;
    linkQueue<int> truck;
    cin >> N;
    for (int i=0; i<N; ++i)
    {
        int type;
        cin >> type;
        if (type==0) //bus
        {
            ++busNum;
            int time;
            cin >> time;
            bus.enQueue(time);
        }
        else //truck
        {
            ++truNum;
            int time;
            cin >> time;
            truck.enQueue(time);
        }
    }
    int cnt=0;
    int busTime=0, truTime=0;
    while (true)
    {
        int bus_num=0, tru_num=0;
        while (!bus.isEmpty() && bus_num<8 && bus.getHead()<=10*cnt)
        {
            busTime += 10*cnt-bus.deQueue();
            ++bus_num;
        }
        while (!truck.isEmpty() && tru_num<10-bus_num && truck.getHead()<=10*cnt)
        {
            truTime += 10*cnt-truck.deQueue();
            ++tru_num;
        }
        if (bus.isEmpty() && truck.isEmpty())
            break;
        ++cnt;
    }
    float busAverageWaitingTime=(float)busTime/busNum;
    float truAverageWaitingTime=(float)truTime/truNum;
    cout <<setprecision(3)<<std::fixed<< busAverageWaitingTime <<' '<<setprecision(3)<<std::fixed<< truAverageWaitingTime;
}
