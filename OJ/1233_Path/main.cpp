#include <iostream>
#include "adjListGraph.cpp"
using namespace std;

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
