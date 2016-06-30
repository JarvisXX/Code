//adjListGraph.h
#ifndef adjLG
#define adjLG
#include <iostream>
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
    verNode *verList;
    int Vers, Edges;
public:
    adjListGraph(int vSize, const TypeOfVer d[]);
    ~adjListGraph();
    bool insert(int u, int v, TypeOfEdge w);
    int prim(TypeOfEdge noEdge) const;
};
#endif
