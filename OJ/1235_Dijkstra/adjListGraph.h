//adjListGraph.h
#ifndef adjLG
#define adjLG
#include <limits.h>
template <class TypeOfVer, class TypeOfEdge>
class adjListGraph
{
private:
    struct edgeNode
    {
        int end;
        TypeOfEdge weight;
        edgeNode *next;
        edgeNode()
        {
            end = -1;
            weight = INT_MAX;
            next = NULL;
        }
        edgeNode(int e, TypeOfEdge w, edgeNode *n=NULL)
        {
            end = e;
            weight = w;
            next = n;
        }
        bool operator<(const edgeNode &eN) const
        {
            return weight<eN.weight;
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
    void printPath(int start, int end, int prev[]) const;
public:
    adjListGraph(int vSize, const TypeOfVer d[]);
    ~adjListGraph();
    bool insert(int u, int v, TypeOfEdge w);
    void dijkstra(int start, int end, TypeOfEdge noEdge) const;
};
#endif
