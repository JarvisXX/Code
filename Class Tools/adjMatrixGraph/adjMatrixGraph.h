//adjMatrixGraph.h
#ifndef adjMG
#define adjMG
#include "graph.h"
template <class TypeOfVer, class TypeOfEdge>
class adjMatrixGraph:public graph<TypeOfEdge>
{
public:
    adjMatrixGraph(int vSize, const TypeOfVer d[], TypeOfEdge noEdgeFlag);
    bool insert(int u, int v, TypeOfEdge w);
    bool remove(int u, int v);
    bool exist(int u, int v) const;
    ~adjMatrixGraph();
private:
    TypeOfEdge **edge;
    TypeOfVer *ver;
    TypeOfEdge noEdge;
};
#endif

