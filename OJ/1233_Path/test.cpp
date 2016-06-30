#include <iostream>
using namespace std;

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
    void dfs(int start, bool visited[], int cnt, int M, int &result) const;
    int Vers, Edges;
public:
    adjListGraph(int vSize, const TypeOfVer d[]);
    ~adjListGraph();
    bool insert(int u, int v, TypeOfEdge w);
    int searchPath(int start, int M);
};

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
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[], int cnt, int M, int &result) const
{
    if (cnt==M)
    {
        ++result;
        return;
    }
    edgeNode *p=verList[start].head;
    visited[start] = true;
    while (p!=NULL)
    {
        if (visited[p->end]==false)
            dfs(p->end, visited, cnt+1, M, result);
        p = p->next;
    }
    visited[start] = false;
}

template <class TypeOfVer, class TypeOfEdge>
int adjListGraph<TypeOfVer, TypeOfEdge>::searchPath(int start, int M)
{
    bool *visited=new bool[Vers];
    for (int i=0; i<Vers; ++i)
        visited[i] = false;

    int result=0;
    int cnt=0;
    dfs(start, visited, cnt, M, result);

    return result;
}

int main()
{
    int n, m, start, M;
    int ver[10];

    cin >> n >> m >> start >> M;
    for (int i=1; i<=n; ++i)
        ver[i-1] = i;
    adjListGraph<int, int> ALG(n, ver);
    for (int i=0; i<m; ++i)
    {
        int a, b;
        cin >> a >> b;
        ALG.insert(a-1, b-1, 0);
    }

    cout << ALG.searchPath(start-1, M);
}

