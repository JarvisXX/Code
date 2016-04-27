#include <iostream>
#include "seqStack.h"
#include "seqStack.cpp"
using namespace std;

int main()
{
    seqStack<char> a(10);
    for (int i=0; i<20; ++i)
        a.push(char(i+97));
    while (true)
    {
        cout << a.getTop() <<endl;
        cout << a.pop() <<endl;
    }
}
