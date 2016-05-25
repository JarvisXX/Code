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
    struct EulerNode
    {
        int NodeNum;
        EulerNode *next;
        EulerNode(int ver)
        {
            NodeNum = ver;
            next = NULL;
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
    void dfs(int start, bool visited[]) const;
    verNode* clone() const;
    EulerNode* EulerCircuit(int start, EulerNode* &end);
    void printPath(int start, int end, int prev[]) const;
public:
    adjListGraph(int vSize, const TypeOfVer d[]);
    ~adjListGraph();
    bool insert(int u, int v, TypeOfEdge w);
    bool remove(int u, int v);
    bool exist(int u, int v) const;
    void dfs() const;
    void bfs() const;
    void EulerCircuit(TypeOfVer start);
    void topSort() const;
    void kruskal() const;
    void prim(TypeOfEdge noEdge) const;
    void unweightedShortDistance(TypeOfVer start, TypeOfEdge noEdge) const;
};
#endif
