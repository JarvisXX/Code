#include <iostream>
#include "linkList.cpp"
using namespace std;

int main()
{
    linkList<char> a;
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

    cout << "merge" <<endl;
    linkList<char> b;
    for (int i=0; i<10; ++i)
        b.insert(i, char(i+97));
    b.traverse();
    a.merge(b);
    a.traverse();
}
