#include <iostream>
#include "AvlTree.cpp"
using namespace std;

int main()
{
    int a[]={1,2,3,4,5,6};
    AvlTree<int> tree;
    for (int i=0; i<sizeof(a)/sizeof(int); ++i)
        tree.insert(a[i]);
    tree.levelOrder();
    cout << endl;
    cout << "find 6 is " << (tree.find(6)?"true":"false") <<endl;
    tree.remove(6);
    cout << "after delete 6, find 6 is " << (tree.find(6)?"true":"false") <<endl;
    tree.levelOrder();
    cout << endl;
    cout << "find 1 is " << (tree.find(1)?"true":"false") <<endl;
    tree.remove(1);
    cout << "after delete 1, find 1 is " << (tree.find(1)?"true":"false") <<endl;
    tree.levelOrder();
    cout << endl;
    cout << "find 100 is " << (tree.find(100)?"true":"false") <<endl;
    tree.remove(100);
    cout << "after delete 100, find 100 is " << (tree.find(100)?"true":"false") <<endl;
    tree.levelOrder();
    cout << endl;
    return 0;
}
