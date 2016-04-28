#include <iostream>
#include "BinarySearchTree.cpp"
using namespace std;

int main()
{
    int a[]={10,8,6,21,87,56,4,0,11,3,22,7,5,34,1,2,9};
    BinarySearchTree<int> tree;
    for (int i=0; i<sizeof(a)/sizeof(int); ++i)
        tree.insert(a[i]);
    cout << "find 2 is " << (tree.find(2)?"true":"false") <<endl;
    tree.remove(2);
    cout << "after delete 2, find 2 is " << (tree.find(2)?"true":"false") <<endl;
    cout << "find 3 is " << (tree.find(3)?"true":"false") <<endl;
    tree.remove(3);
    cout << "after delete 3, find 3 is " << (tree.find(3)?"true":"false") <<endl;
    cout << "find 100 is " << (tree.find(100)?"true":"false") <<endl;
    tree.remove(100);
    cout << "after delete 100, find 100 is " << (tree.find(100)?"true":"false") <<endl;
    return 0;
}
