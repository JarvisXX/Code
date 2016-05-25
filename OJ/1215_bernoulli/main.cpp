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
            int a;
            cin >> a;
            pQueue.enQueue(a);
        }
        else if (op=="delete")
            pQueue.deQueue();
        else if (op=="min")
            cout << pQueue.getHead() <<endl;
    }
}
