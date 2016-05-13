#include "adjListGraph.h"

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
adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[]) const
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
