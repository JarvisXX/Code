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
