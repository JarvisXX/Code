#include <iostream>
using namespace std;

int main()
{
    int m, n, a, b, c, d;
    int field[1010][1010];
    int input;
    int value, maxValue;
    int pyramidX, pyramidY, tombX, tombY;
    maxValue = 0;

    cin >> m >> n >> a >> b >> c >> d;
    for (int j=1; j<=n; ++j)
    {
        for (int i=1; i<=m; ++i)
        {
            cin >> input;
            field[i][j] = field[i-1][j] + field[i][j-1] - field[i-1][j-1] +input;
        }
    }
    for (int i=1; i+a-1<=m; ++i)
    {
        for (int j=1; j+b-1<=n; ++j)
        {
            for (int k=i+1; k+c<=i+a-1; ++k)
            {
                for (int l=j+1; l+d<=j+b-1; ++l)
                {
                    value = field[i+a-1][j+b-1]-field[i-1][j+b-1]-field[i+a-1][j-1]+field[i-1][j-1]
                            -(field[k+c-1][l+d-1]-field[k-1][l+d-1]-field[k+c-1][l-1]+field[k-1][l-1]);
                    if (value>maxValue)
                    {
                        maxValue = value;
                        pyramidX = i;
                        pyramidY = j;
                        tombX = k;
                        tombY = l;
                    }
                }
            }
        }
    }
    cout << pyramidX <<' '<< pyramidY <<endl;
    cout << tombX <<' '<< tombY <<endl;
}
