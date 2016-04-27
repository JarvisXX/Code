#include <iostream>
#include "seqList.h"
#include "seqList.cpp"
using namespace std;

int main()
{
    seqList<char> a(10);
    for (int i=0; i<20; ++i)
        a.insert(i, char(i+97));

    a.traverse();
    cout << a.length() << endl;
    cout << a.search('a') << endl;
    cout << a.search('z') << endl;
    cout << a.visit(10) << endl;
    a.remove(2);
    a.traverse();
    cout << a.length() << endl;
    a.clear();
    a.traverse();
    cout << a.length() << endl;
}
