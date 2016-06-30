#include <iostream>
#include "adjListGraph.cpp"
using namespace std;

int main()
{
    int n, m;
    int ver[10010];
    int a, b, p;

    cin >> n >> m;
    for (int i=0; i<n; ++i)
        ver[i] = i+1;
    adjListGraph<int, int> ALG(n, ver);
    for (int i=0; i<m; ++i)
    {
        cin >> a >> b >> p;
        ALG.insert(a-1, b-1, p);
    }
    //cout << "Prim:\n";
    //cout << ALG.prim(110) <<endl;
    cout << "Kruskal:\n";
    cout << ALG.kruskal() <<endl;
}
