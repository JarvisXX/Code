#include <iostream>
#include <cstring>
#include "BinaryTree.cpp"
using namespace std;

int main()
{
    int N;
    int lt[100010], rt[100010], wt[100010];
    bool searchRoot[100010];
    int root;

    cin >> N;
    memset(searchRoot, 0, sizeof(searchRoot));
    for (int i=1; i<=N; ++i)
    {
        cin >> lt[i] >> rt[i] >> wt[i];
        searchRoot[lt[i]] = 1;
        searchRoot[rt[i]] = 1;
    }
    for (int i=1; i<=N; ++i)
    {
        if (searchRoot[i]==0)
        {
            root = i;
            break;
        }
    }
    BinaryTree<int> tree;
    tree.createTree(0, root, lt, rt);
    tree.preOrder(wt);
    tree.postOrder(wt);
    tree.midOrder(wt);
    tree.levelOrder(wt);
}
