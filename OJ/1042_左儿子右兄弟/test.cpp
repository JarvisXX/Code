#include <iostream>
#include <cstdlib>
#include <cstring>
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

struct Node
{
    int child;
    int brother;
    Node(int c, int b):child(c), brother(b) {}
    ~Node() {}
}**tree;

void preOrder(int t)
{
    if (t!=0)
    {
        cout << t <<' ';
        preOrder(tree[t]->child);
        preOrder(tree[t]->brother);
    }
}

void postOrder(int t)
{
    if (t!=0)
    {
        postOrder(tree[t]->child);
        cout << t <<' ';
        postOrder(tree[t]->brother);
    }
}
linkQueue<int> que;
void levelOrder(int t)
{
    if (t!=0)
    {
        cout << t <<' ';
        que.enQueue(t);
        levelOrder(tree[t]->brother);
        while (!que.isEmpty())
            levelOrder(tree[que.deQueue()]->child);
    }
}

int main()
{
    int N;
    int root;

    cin >> N;
    tree = new Node*[N+10];
    bool flag[15000];
    memset(flag, 0, sizeof(flag));
    for (int i=1; i<=N; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        tree[a] = new Node(b, c);
        flag[b] = 1;
        flag[c] = 1;
    }
    for (int i=1; i<=N; ++i)
    {
        if (flag[i]==0)
        {
            root = i;
            break;
        }
    }
    preOrder(root);
    cout <<endl;
    postOrder(root);
    cout <<endl;
    levelOrder(root);
}

