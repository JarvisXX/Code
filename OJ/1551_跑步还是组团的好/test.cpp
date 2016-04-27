#include <iostream>
#include <cstdlib>
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

int main()
{
    linkStack<int> pos;
    linkStack<int> speed;
    int N;
    int P, V;

    cin >> N;
    for (int i=0; i<N; ++i)
    {
        cin >> P >> V;
        if (speed.isEmpty())
        {
            pos.push(P);
            speed.push(V);
        }
        else
        {
            if (P==pos.getTop())
            {
                if (V<speed.getTop())
                {
                    pos.pop();
                    speed.pop();
                    pos.push(P);
                    speed.push(V);
                }
                else
                    continue;
            }
            else
            {
                while (!speed.isEmpty() && V<speed.getTop())
                {
                    pos.pop();
                    speed.pop();
                }
                pos.push(P);
                speed.push(V);
            }
        }
    }
    int cnt=0;
    while (!speed.isEmpty())
    {
        speed.pop();
        ++cnt;
    }
    cout << cnt;
}
