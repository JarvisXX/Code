#include <iostream>
#include "adjListGraph.cpp"
using namespace std;

int main()
{
    int n;
    while (cin >> n)
    {
        if (n==0)
            break;
        char ver[30];
        for (int i=0; i<n; ++i)
            ver[i] = char('A'+i);
        adjListGraph<char, int> ALG(n, ver);
        for (int i=0; i<n-1; ++i)
        {
            char a, b;
            int k, cost;
            cin >> a >> k;
            for (int j=0; j<k; ++j)
            {
                cin >> b >> cost;
                ALG.insert(int(a-'A'), int(b-'A'), cost);
            }
        }
        cout << ALG.prim(110) <<endl;
    }
}
