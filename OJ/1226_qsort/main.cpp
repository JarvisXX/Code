#include <iostream>
using namespace std;

void Qsort(int a[], int low, int high)
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
            ++first;
            --last;
        }
    }

    if (first<high)
        Qsort(a, first, high);
    if (last>low)
        Qsort(a, low, last);
}

int main()
{
    int N;
    int array[100010];

    cin >> N;
    for (int i=0; i<N; ++i)
        cin >> array[i];
    Qsort(array, 0, N-1);
    for (int i=0; i<N; ++i)
        cout << array[i] <<' ';
}
