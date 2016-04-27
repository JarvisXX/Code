#include <iostream>
#include "priorityQueue.cpp"
using namespace std;

int main()
{
    int data[10]={5,10,7,3,2,55,40,1,84,12};
    priorityQueue<int> pQueue(data, 10);
    pQueue.enQueue(100);
    while (!pQueue.isEmpty())
    {
        cout << pQueue.deQueue() <<endl;
    }
}
