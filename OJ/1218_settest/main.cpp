#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    bool *array=new bool [10010];
    memset(array, 0, 10010);
    int n, m;
    int currentSize=0;

    cin >> n;
    for (int i=0; i<n; ++i)
    {
        char c;
        cin >> c >> m;
        if (c=='+')
        {
            for (int j=0; j<m; ++j)
            {
                int num;
                cin >> num;
                if (array[num]==0)
                {
                    array[num] = 1;
                    ++currentSize;
                }

            }
        }
        else if (c=='-')
        {
            for (int j=0; j<m; ++j)
            {
                int num;
                cin >> num;
                if (array[num]==1)
                {
                    array[num] = 0;
                    --currentSize;
                }
            }
        }
        else if (c=='*')
        {
            bool *tmp=new bool [10010];
            memset(tmp, 0, 10010);
            currentSize = 0;
            for (int j=0; j<m; ++j)
            {
                int num;
                cin >> num;
                if (array[num]==1)
                {
                    tmp[num] = 1;
                    ++currentSize;
                }
            }
            delete [] array;
            array = tmp;
        }

        int cnt=0;
        for (int j=0; cnt!=currentSize; ++j)
        {
            if (array[j]==1)
            {
                cout << j <<' ';
                ++cnt;
            }
        }
        cout << endl;
    }
}
