#include <iostream>
using namespace std;

void Qsort(int a[], int b[], int low, int high)
{
    int first = low;
    int last = high;
    int key = a[(low+high)/2];
    int mid;

    while (first<=last)
    {	while (a[first]<key)
            ++first;
        while (a[last]>key)
            --last;
        if (first<=last)
        {
            mid = a[first];
            a[first] = a[last];
            a[last] = mid;
            mid = b[first];
            b[first] = b[last];
            b[last] = mid;
            ++first;
            --last;
        }
    }

    if (first<high)
        Qsort(a, b, first, high);
    if (last>low)
        Qsort(a, b, low, last);
}

int main()
{
    int N, D;
    int x[50010];
    int h[50010];
    bool cattleL[50010];
    bool cattleR[50010];

    cin >> N >> D;
    for (int i=0; i<N; ++i)
        cin >> x[i] >> h[i];
    Qsort(h, x, 0, N-1);
    int cnt=0;
    for (int i=0; i<N; ++i)
    {
        for (int j=N-1; j>i; --j)
        {
            if (h[j]>=2*h[i] && x[i]-x[j]<=D && x[i]-x[j]>0)
                cattleL[i] = 1;
            if (h[j]>=2*h[i] && x[j]-x[i]<=D && x[j]-x[i]>0)
                cattleR[i] = 1;
            if (cattleL[i] && cattleR[i])
            {
                ++cnt;
                break;
            }
            if (h[j]<2*h[i])
                break;
        }
    }
    cout << cnt;
}
