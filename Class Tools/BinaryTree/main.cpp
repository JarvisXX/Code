#include <iostream>
#include "BinaryTree.cpp"
using namespace std;

int main()
{
    BinaryTree<char> tree, tree1('M'), tree2;
    tree.createTree('@');

    cout << "Height: " << tree.height() <<endl;
    cout << "Size: " << tree.size() <<endl;
    tree.preOrder();
    tree.midOrder();
    tree.postOrder();

    tree2.makeTree('Y', tree, tree1);
    cout << endl;
    cout << "Height: " << tree2.height() <<endl;
    cout << "Size: " << tree2.size() <<endl;
    tree2.preOrder();
    tree2.midOrder();
    tree2.postOrder();
    return 0;
}
