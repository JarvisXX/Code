#include <iostream>
#include "linkQueue.h"
#include "linkQueue.cpp"
using namespace std;

int main()
{
    linkQueue<int> s;
    for (int i=0; i<10; ++i)
        s.enQueue(2*i);
    while (!s.isEmpty())
    {
        cout << s.getHead() <<' ';
        cout << s.deQueue() <<' ';
    }
    cout <<endl;
}
