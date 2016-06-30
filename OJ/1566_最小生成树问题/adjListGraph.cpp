#include <iostream>
#include "adjListGraph.h"
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
    verList[v].head = new edgeNode(u, w, verList[v].head);
    ++Edges;
    return true;
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
