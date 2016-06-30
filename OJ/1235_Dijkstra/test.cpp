#include <iostream>
#include <limits.h>
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

template <class TypeOfVer, class TypeOfEdge>
class adjListGraph
{
private:
    struct edgeNode
    {
        int end;
        TypeOfEdge weight;
        edgeNode *next;
        edgeNode()
        {
            end = -1;
            weight = INT_MAX;
            next = NULL;
        }
        edgeNode(int e, TypeOfEdge w, edgeNode *n=NULL)
        {
            end = e;
            weight = w;
            next = n;
        }
        bool operator<(const edgeNode &eN) const
        {
            return weight<eN.weight;
        }
    };
    struct verNode
    {
        TypeOfVer ver;
        edgeNode *head;
        verNode(edgeNode *h=NULL)
        {
            head = h;
        }
    };
    verNode *verList;
    int Vers, Edges;
    void printPath(int start, int end, int prev[]) const;
public:
    adjListGraph(int vSize, const TypeOfVer d[]);
    ~adjListGraph();
    bool insert(int u, int v, TypeOfEdge w);
    void dijkstra(int start, int end, TypeOfEdge noEdge) const;
};

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer d[])
{
    Vers = vSize;
    Edges = 0;
    verList = new verNode[vSize];
    for (int i=0; i<Vers; ++i)
        verList[i].ver = d[i];
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph()
{
    /*
    edgeNode *p;
    for (int i=0; i<Vers; ++i)
        while ((p=verList[i].head)!=NULL)
        {
            verList[i].head = p->next;
            delete p;
        }
    delete [] verList;
    */
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::insert(int u, int v, TypeOfEdge w)
{
    verList[u].head = new edgeNode(v, w, verList[u].head);
    ++Edges;
    return true;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dijkstra(int start, int end, TypeOfEdge noEdge) const
{
    TypeOfEdge *distance=new TypeOfEdge[Vers];
    priorityQueue<edgeNode> pq(Vers);
    int *prev=new int [Vers];
    bool *known=new bool [Vers];
    int *num=new int [Vers];
    edgeNode *p;

    for (int i=0; i<Vers; ++i)
    {
        known[i] = false;
        distance[i] = noEdge;
    }

    distance[start] = 0;
    prev[start] = start;
    num[start] = 1;
    pq.enQueue(edgeNode(start, 0));

    while (!pq.isEmpty())
    {
        edgeNode tmp=pq.deQueue();
        if (known[tmp.end])
            continue;
        known[tmp.end] = true;
        if (tmp.end==end)
            break;
        for (p=verList[tmp.end].head; p!=NULL; p=p->next)
            if (!known[p->end])
            {
                if (distance[p->end]>distance[tmp.end]+p->weight)
                {
                    distance[p->end] = distance[tmp.end]+p->weight;
                    prev[p->end] = tmp.end;
                    num[p->end]=num[tmp.end]+1;
                    pq.enQueue(edgeNode(p->end, distance[p->end]));
                }
                else if (distance[p->end]==distance[tmp.end]+p->weight)
                {
                    if (num[p->end]>num[tmp.end]+1)
                    {
                        prev[p->end]=tmp.end;
                        num[p->end]=num[tmp.end]+1;
                    }
                }
            }
    }

    cout << distance[end] <<endl;
    printPath(start, end, prev);
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::printPath(int start, int end, int prev[]) const
{
    if (start==end)
    {
        cout << verList[start].ver;
        return;
    }
    printPath(start, prev[end], prev);
    cout <<' '<< verList[end].ver;
}

int main()
{
    int n, m, start, end;
    int ver[1000];
    int a, b, p;

    cin >> n >> m >> start >> end;
    for (int i=0; i<n; ++i)
        ver[i] = i+1;
    adjListGraph<int, int> ALG(n, ver);
    for (int i=0; i<m; ++i)
    {
        cin >> a >> b >> p;
        ALG.insert(a-1, b-1, p);
    }
    ALG.dijkstra(start-1, end-1, INT_MAX);
}
