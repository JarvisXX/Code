#include <iostream>
#include <limits.h>
using namespace std;

template <class TypeOfVer, class TypeOfEdge>
class adjListGraph
{
private:
    struct edgeNode
    {
        int end;
        TypeOfEdge dist;
        TypeOfEdge price;
        edgeNode *next;
        edgeNode(int e, TypeOfEdge d, TypeOfEdge p, edgeNode *n=NULL)
        {
            end = e;
            dist = d;
            price = p;
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
    void dfs(int s, int t, int dist, int price, int &Dist, int &Price, bool visited[]) const;
    int Vers, Edges;
public:
    adjListGraph(int vSize, const TypeOfVer d[]);
    ~adjListGraph();
    bool insert(int u, int v, TypeOfEdge d, TypeOfEdge p);
    void wShortDistPath(int s, int t, int &Dist, int &Price) const;
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
    /*
    edgeNode *p;
    for (int i=0; i<Vers; ++i)
    {
        p=verList[i].head;
        while (p!=NULL)
        {
            verList[i].head = p->next;
            delete p;
            p = verList[i].head;
        }
    }
    delete [] verList;
    */
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::insert(int u, int v, TypeOfEdge d, TypeOfEdge p)
{
    verList[u].head = new edgeNode(v, d, p, verList[u].head);
    verList[v].head = new edgeNode(u, d, p, verList[v].head);
    ++Edges;
    return true;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int s, int t, int dist, int price, int &Dist, int &Price, bool visited[]) const
{
    if (s==t)
    {
        if (dist<Dist)
        {
            Dist = dist;
            Price = price;
        }
        else if (dist==Dist)
        {
            if (price<Price)
                Price = price;
        }
        return;
    }
    edgeNode *p=verList[s].head;
    visited[s] = true;
    while (p!=NULL)
    {
        if (visited[p->end]==false)
            dfs(p->end, t, dist+p->dist, price+p->price, Dist, Price, visited);
        p = p->next;
    }
    visited[s] = false;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::wShortDistPath(int s, int t, int &Dist, int &Price) const
{
    int dist=0, price=0;
    bool *visited=new bool[Vers];
    for (int i=0; i<Vers; ++i)
        visited[i] = false;

    dfs(s, t, dist, price, Dist, Price, visited);
}

int main()
{
    int Dist=INT_MAX, Price=INT_MAX;
    int n, m;
    int ver[1010];
    int a, b, d, p;
    int s, t;

    cin >> n >> m;
    for (int i=0; i<n; ++i)
        ver[i] = i+1;
    adjListGraph<int, int> ALG(n, ver);
    for (int i=0; i<m; ++i)
    {
        cin >> a >> b >> d >> p;
        ALG.insert(a-1, b-1, d, p);
    }
    cin >> s >> t;
    ALG.wShortDistPath(s-1, t-1, Dist, Price);

    cout << Dist <<' '<< Price;
}
