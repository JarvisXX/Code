#include <iostream>
#include "linkStack.h"
#include "linkStack.cpp"
using namespace std;

int main()
{
    linkStack<char> a;
    for (int i=0; i<20; ++i)
        a.push(char(i+97));
    while (true)
    {
        cout << a.getTop() <<endl;
        cout << a.pop() <<endl;
    }
}
