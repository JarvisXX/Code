#include <iostream>
#include <limits.h>
#include "adjListGraph.cpp"
using namespace std;

int main()
{
    int n, m, start, end;
    int ver[1000];
    int a, b, p;

    cin >> n >> m >> start >> end;
    for (int i=0; i<n; ++i)
        ver[i] = i+1;
    adjListGraph<int, int> ALG(n, ver);
    for (int i=0; i<m; ++i)
    {
        cin >> a >> b >> p;
        ALG.insert(a-1, b-1, p);
    }
    ALG.dijkstra(start-1, end-1, INT_MAX);
}
