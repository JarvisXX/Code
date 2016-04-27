#include <iostream>
#include "seqQueue.h"
#include "seqQueue.cpp"
using namespace std;

int main()
{
    seqQueue<char> a(10);
    for (int i=0; i<20; ++i)
        a.enQueue(char(i+97));
    while (!a.isEmpty())
    {
        cout << a.getHead() <<endl;
        cout << a.deQueue() <<endl;
    }
}
