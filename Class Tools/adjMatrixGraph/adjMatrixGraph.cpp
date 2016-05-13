#include "adjMatrixGraph.h"

template <class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::adjMatrixGraph(int vSize, const TypeOfVer d[], TypeOfEdge noEdgeFlag)
{
    Vers = vSize;
    Edges = 0;
    noEdge = noEdgeFlag;

    ver = new TypeOfVer[vSize];
    for (int i=0; i<vSize; ++i)
        ver[i] = d[i];
    edge = new TypeOfEdge*[vSize];
    for (int i=0; i<vSize; ++i)
    {
        edge[i] = new TypeOfEdge[vSize];
        for (int j=0; j<vSize; ++j)
            edge[i][j] = noEdge;
        edge[i][i] = 0;
    }
}

template <class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::~adjMatrixGraph()
{
    delete [] ver;
    for (int i=0; i<Vers; ++i)
        delete [] edge[i];
    delete [] edge;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::insert(int u, int v, TypeOfEdge w)
{
    if (u<0 || u>Vers-1 || v<0 || v>Vers-1)
        return false;
    if (edge[u][v]!=noEdge)
        return false;
    edge[u][v] = w;
    ++Edges;
    return true;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::remove(int u, int v)
{
    if (u<0 || u>Vers-1 || v<0 || v>Vers-1)
        return false;
    if (edge[u][v]==noEdge)
        return false;
    edge[u][v] = noEdge;
    --Edges;
    return true;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::exist(int u, int v) const
{
    if (u<0 || u>Vers-1 || v<0 || v>Vers-1)
        return false;
    if (edge[u][v]==noEdge)
        return false;
    else
        return true;
}
