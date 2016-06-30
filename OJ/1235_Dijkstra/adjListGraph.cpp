#include <iostream>
#include "adjListGraph.h"
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
    /*
    for (i=1; i<Vers; ++i)
    {
        min = noEdge;
        for (j=0; j<Vers; ++j)
            if (!known[j] && distance[j]<min)
            {
                min = distance[j];
                u = j;
            }
        known[u] = true;
        for (p=verList[u].head; p!=NULL; p=p->next)
            if (!known[p->end] && distance[p->end]>min+p->weight)
            {
                distance[p->end] = min+p->weight;
                prev[p->end] = u;
            }
    }
    */
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
