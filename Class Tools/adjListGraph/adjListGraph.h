//adjListGraph.h
#ifndef adjLG
#define adjLG
#include <iostream>
#include "graph.h"
template <class TypeOfVer, class TypeOfEdge>
class adjListGraph:public graph<TypeOfEdge>
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
    void dfs(int start, bool visited[]) const;
public:
    adjListGraph(int vSize, const TypeOfVer d[]);
    ~adjListGraph();
    bool insert(int u, int v, TypeOfEdge w);
    bool remove(int u, int v);
    bool exist(int u, int v) const;
    void dfs() const;
};
#endif
