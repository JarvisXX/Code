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

class DisjointSet
{
private:
    int size;
    int *parent;
public:
    DisjointSet(int s);
    ~DisjointSet() {delete [] parent;}
    void Union(int root1, int root2);
    int Find(int x);
};

DisjointSet::DisjointSet(int n)
{
    size = n;
    parent = new int [size];
    for (int i=0; i<size; ++i)
        parent[i] = -1;
}

int DisjointSet::Find(int x)
{
    if (parent[x]<0)
        return x;
    return parent[x]=Find(parent[x]);
}

void DisjointSet::Union(int root1, int root2)
{
    if (root1==root2)
        return;
    if (parent[root1]>parent[root2])
    {
        parent[root2] += parent[root1];
        parent[root1] = root2;
    }
    else
    {
        parent[root1] += parent[root2];
        parent[root2] = root1;
    }
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
        edgeNode(int e, TypeOfEdge w, edgeNode *n=NULL)
        {
            end = e;
            weight = w;
            next = n;
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
    struct edge
    {
        int beg, end;
        TypeOfEdge w;
        bool operator<(const edge &rp) const
        {
            return w<rp.w;
        }
    };
    verNode *verList;
    int Vers, Edges;
public:
    adjListGraph(int vSize, const TypeOfVer d[]);
    ~adjListGraph();
    bool insert(int u, int v, TypeOfEdge w);
    int kruskal() const;
    int prim(TypeOfEdge noEdge) const;
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
    edgeNode *p;
    for (int i=0; i<Vers; ++i)
        while ((p=verList[i].head)!=NULL)
        {
            verList[i].head = p->next;
            delete p;
        }
    delete [] verList;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::insert(int u, int v, TypeOfEdge w)
{
    verList[u].head = new edgeNode(v, w, verList[u].head);
    verList[v].head = new edgeNode(u, w, verList[v].head);
    ++Edges;
    return true;
}

template <class TypeOfVer, class TypeOfEdge>
int adjListGraph<TypeOfVer, TypeOfEdge>::kruskal() const
{
    int edgesAccepted=0, u, v;
    edgeNode *p;
    edge e;
    DisjointSet ds(Vers);
    priorityQueue<edge> pq;
    int result=0;

    for (int i=0; i<Vers; ++i)
    {
        for (p=verList[i].head; p!=NULL; p=p->next)
            if (i<p->end)
            {
                e.beg = i;
                e.end = p->end;
                e.w = p->weight;
                pq.enQueue(e);
            }
    }

    while (edgesAccepted<Vers-1)
    {
        e = pq.deQueue();
        u = ds.Find(e.beg);
        v = ds.Find(e.end);
        if (u!=v)
        {
            ++edgesAccepted;
            ds.Union(u, v);
            //cout <<'('<< verList[e.beg].ver <<','<< verList[e.end].ver <<") ";
            result += e.w;
            //cout << "weight:" <<e.w<<" result:"<<result<<endl;
        }
    }

    return result;
}

template <class TypeOfVer, class TypeOfEdge>
int adjListGraph<TypeOfVer, TypeOfEdge>::prim(TypeOfEdge noEdge) const
{
    bool *flag=new bool [Vers];
    TypeOfEdge *lowCost=new TypeOfEdge[Vers];
    int *startNode=new int [Vers];
    edgeNode *p;
    TypeOfEdge min;
    int start, i, j;
    int result=0;

    for (i=0; i<Vers; ++i)
    {
        flag[i] = false;
        lowCost[i] = noEdge;
    }
    start = 0;
    for (i=1; i<Vers; ++i)
    {
        for (p=verList[start].head; p!=NULL; p=p->next)
            if (!flag[p->end] && (lowCost[p->end] > p->weight))
            {
                lowCost[p->end] = p->weight;
                startNode[p->end] = start;
            }
        flag[start] = true;
        min = noEdge;
        for (j=0; j<Vers; ++j)
            if (lowCost[j]<min)
            {
                min = lowCost[j];
                start = j;
            }
        //cout <<'('<< verList[startNode[start]].ver <<','<< verList[start].ver <<") ";
        result += min;
        //cout << "min:" <<min<<" result:"<<result<<endl;
        lowCost[start] = noEdge;
    }

    delete [] flag;
    delete [] startNode;
    delete [] lowCost;

    return result;
}

int main()
{
    int n, m;
    int ver[10010];
    int a, b, p;

    cin >> n >> m;
    for (int i=0; i<n; ++i)
        ver[i] = i+1;
    adjListGraph<int, int> ALG(n, ver);
    for (int i=0; i<m; ++i)
    {
        cin >> a >> b >> p;
        ALG.insert(a-1, b-1, p);
    }
    //cout << "Prim:\n";
    //cout << ALG.prim(110) <<endl;
    //cout << "Kruskal:\n";
    cout << ALG.kruskal() <<endl;
}
