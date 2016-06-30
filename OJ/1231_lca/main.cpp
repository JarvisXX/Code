//Lowest Common Ancestors
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int N, X, Y;
    int a, b;
    int father[1000];
    int depth[1000];
    memset(depth, 0, sizeof(depth));
    memset(father, 0, sizeof(father));

    cin >> N >> X >> Y;
    depth[1] = 1;
    for (int i=1; i<=N; ++i)
    {
        cin >> a >> b;
        father[a] = i;
        father[b] = i;
        depth[a] = depth[i]+1;
        depth[b] = depth[i]+1;
    }
    int x, y, x_depth, y_depth;
    x = X;
    y = Y;
    x_depth = depth[x];
    y_depth = depth[y];
    while (x_depth!=y_depth)
    {
        if (x_depth<y_depth)
        {
            y = father[y];
            --y_depth;
        }
        else
        {
            x = father[x];
            --x_depth;
        }
    }
    while (x!=y)
    {
        x = father[x];
        y = father[y];
    }
    cout << x;
}
