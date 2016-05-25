#include <iostream>
#include "adjListGraph.h"
#include "linkQueue.cpp"
#include "priorityQueue.cpp"
using namespace std;

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
    ++Edges;
    return true;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::remove(int u, int v)
{
    edgeNode *p=verList[u].head, *q;
    if (p==NULL)
        return false;
    if (p->end==v)
    {
        verList[u].head = p->next;
        delete p;
        --Edges;
        return true;
    }
    while (p->next!=NULL && p->next->end!=v)
        p = p->next;
    if (p->next==NULL)
        return false;
    q = p->next;
    p->next = q->next;
    delete q;
    --Edges;
    return true;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(int u, int v) const
{
    edgeNode *p=verList[u].head;
    while (p!=NULL && p->end!=v)
        p = p->next;
    if (p==NULL)
        return false;
    else
        return true;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs() const
{
    bool *visited=new bool[Vers];
    for (int i=0; i<Vers; ++i)
        visited[i] = false;

    cout << "DFS:" <<endl;
    for (int i=0; i<Vers; ++i)
    {
        if (visited[i]==true)
            continue;
        dfs(i, visited);
        cout << endl;
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::bfs() const
{
    bool *visited = new bool [Vers];
    int currentNode;
    linkQueue<int> q;
    edgeNode *p;
    for (int i=0; i<Vers; ++i)
        visited[i] = false;

    cout << "BFS:" <<endl;
    for (int i=0; i<Vers; ++i)
    {
        if (visited[i]==true)
            continue;
        q.enQueue(i);
        while (!q.isEmpty())
        {
            currentNode = q.deQueue();
            if (visited[currentNode]==true)
                continue;
            cout << verList[currentNode].ver <<'\t';
            visited[currentNode] = true;
            p = verList[currentNode].head;
            while (p!=NULL)
            {
                if (visited[p->end]==false)
                    q.enQueue(p->end);
                p = p->next;
            }
        }
        cout <<endl;
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(TypeOfVer start)
{
    EulerNode *beg, *end, *p, *q, *tb, *te;
    int numOfDegree;
    edgeNode *r;
    verNode *tmp;

    for (int i=0; i<Vers; ++i)
    {
        numOfDegree = 0;
        r = verList[i].head;
        while (r!=0)
        {
            ++numOfDegree;
            r = r->next;
        }
        if (numOfDegree==0 || numOfDegree%2)
        {
            cout << "Euler Curcuit Nonexistent!" <<endl;
            return;
        }
    }

    int i_;
    for (i_=0; i_<Vers; ++i_)
        if (verList[i_].ver==start)
            break;
    if (i_==Vers)
    {
        cout << "Start Vertex Nonexistent!" <<endl;
        return;
    }

    tmp = clone();
    beg = EulerCircuit(i_, end);
    while (true)
    {
        p = beg;
        while (p->next!=NULL)
        {
            if (verList[p->next->NodeNum].head!=NULL)
                break;
            else
                p = p->next;
        }
        if (p->next==NULL)
            break;
        q = p->next;
        tb = EulerCircuit(q->NodeNum, te);
        te->next = q->next;
        p->next = tb;
        delete q;
    }
    delete [] verList;
    verList = tmp;

    cout << "Euler Curcuit:" <<endl;
    while (beg!=NULL)
    {
        cout << verList[beg->NodeNum].ver <<'\t';
        p = beg;
        beg = beg->next;
        delete p;
    }
    cout << endl;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::topSort() const
{
    linkQueue<int> q;
    edgeNode *p;
    int current, *inDegree=new int [Vers];
    for (int i=0; i<Vers; ++i)
        inDegree[i] = 0;
    for (int i=0; i<Vers; ++i)
        for (p=verList[i].head; p!=NULL; p=p->next)
            ++inDegree[p->end];
    for (int i=0; i<Vers; ++i)
        if (inDegree[i]==0)
            q.enQueue(i);
    cout << "topSort:" <<endl;
    while (!q.isEmpty())
    {
        current = q.deQueue();
        cout << verList[current].ver <<'\t';
        for (p=verList[current].head; p!=NULL; p=p->next)
            if (--inDegree[p->end]==0)
                q.enQueue(p->end);
    }
    cout << endl;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::kruskal() const
{
    int edgesAccepted=0, u, v;
    edgeNode *p;
    edge e;
    DisjointSet ds(Vers);
    priorityQueue<edge> pq;

    for (int i=0; i<Vers; ++i)
    {
        for (p=verList[i].head; p!=NULL; p=p->next)
            if (i<p->end)
            {
                e.beg = i;
                e.end = p->end;
                e.w = p->weight;
                pq.edQueue(e);
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
            cout <<'('<< verList[e.ebg].ver <<','<< verList[e.end].ver <<")\t";
        }
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::prim(TypeOfEdge noEdge) const
{
    bool *flag=new bool [Vers];
    TypeOfEdge *lowCost=new TypeOfEdge[Vers];
    int *startNode=new int [Vers];
    edgeNode *p;
    TypeOfEdge min;
    int start, i, j;

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
        cout <<'('<< verList[startNode[start]].ver <<','<< verList[start].ver <<")\t";
        lowCost[start] = noEdge;
    }
    delete [] flag;
    delete [] startNode;
    delete [] lowCost;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::unweightedShortDistance(TypeOfVer start, TypeOfEdge noEdge) const
{
    linkQueue<int> q;
    TypeOfEdge *distance=new TypeOfEdge[Vers];
    int *prev=new int [Vers];
    int u, sNo;
    edgeNode *p;

    for (int i=0; i<Vers; ++i)
        distance[i] = noEdge;

    for (sNo=0; sNo<Vers; ++sNo)
        if (verList[sNo].ver==start)
            break;
    if (sNo==Vers)
    {
        cout << "Start Vertex Nonexistent!" <<endl;
        return;
    }

    distance[sNo] = 0;
    prev[sNo] =sNo;
    q.enQueue(sNo);
    while (!q.isEmpty())
    {
        u = q.deQueue();
        for (p=verList[u].head; p!=NULL; p=p->next)
            if (distance[p->end]==noEdge)
            {
                distance[p->end] = distance[u]+1;
                prev[p->end] = u;
                q.enQueue(p->end);
            }
    }

    for (int i=0; i<Vers; ++i)
    {
        cout << "The path from" << start << "to" << verList[i].ver << "is: " <<endl;
        printPath(sNo, i, prev);
        cout << endl;
    }
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::verNode* adjListGraph<TypeOfVer, TypeOfEdge>::clone() const
{
    verNode *tmp=new verNode[Vers];
    edgeNode *p;

    for (int i=0; i<Vers; ++i)
    {
        tmp[i].ver = verList[i].ver;
        p = verList[i].head;
        while (p!=NULL)
        {
            tmp[i].head = new edgeNode(p->end, p->weight, tmp[i].head);
            p = p->next;
        }
    }
    return tmp;
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::EulerNode* adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(int start, EulerNode* &end)
{
    EulerNode *beg;
    int nextNode;
    beg = end = new EulerNode(start);
    while (verList[start].head!=NULL)
    {
        nextNode = verList[start].head->end;
        remove(start, nextNode);
        remove(nextNode, start);
        start = nextNode;
        end->next = new EulerNode(start);
        end = end->next;
    }
    return beg;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[]) const
{
    edgeNode *p=verList[start].head;
    cout << verList[start].ver <<'\t';
    visited[start] = true;
    while (p!=NULL)
    {
        if (visited[p->end]==false)
            dfs(p->end, visited);
        p = p->next;
    }
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
    cout <<'-'<< verList[end].ver;
}
