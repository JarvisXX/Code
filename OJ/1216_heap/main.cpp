#include <iostream>
#include "priorityQueue.cpp"
using namespace std;

int main()
{
    int M;
    cin >> M;
    priorityQueue<int> pQueue(M);

    string op;
    for (int i=0; i<M; ++i)
    {
        cin >> op;
        if (op=="insert")
        {
            int x;
            cin >> x;
            pQueue.enQueue(x);
        }
        else if (op=="find")
        {
            int x;
            cin >> x;
            int pos=0;
            for (int i=1; i<=pQueue.getSize(); ++i)
                if (pQueue.array[i]>x && (pos==0 || pQueue.array[i]<pQueue.array[pos]))
                    pos = i;
            cout << pos <<endl;
        }
        else if (op=="decrease")
        {
            int i, v;
            cin >> i >> v;
            int x=pQueue.array[i]-v;
            int hole=i;
            for (; hole>1 && x<pQueue.array[hole/2]; hole/=2)
                pQueue.array[hole] = pQueue.array[hole/2];
            pQueue.array[hole] = x;
        }
    }
}
