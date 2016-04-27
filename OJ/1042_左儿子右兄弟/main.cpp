#include <iostream>
#include <cstdlib>
#include <cstring>
#include "linkQueue.cpp"
using namespace std;

struct Node
{
    int child;
    int brother;
    Node(int c, int b):child(c), brother(b) {}
    ~Node() {}
}**tree;

void preOrder(int t)
{
    if (t!=0)
    {
        cout << t <<' ';
        preOrder(tree[t]->child);
        preOrder(tree[t]->brother);
    }
}

void postOrder(int t)
{
    if (t!=0)
    {
        postOrder(tree[t]->child);
        cout << t <<' ';
        postOrder(tree[t]->brother);
    }
}
linkQueue<int> que;
void levelOrder(int t)
{
    if (t!=0)
    {
        cout << t <<' ';
        que.enQueue(t);
        levelOrder(tree[t]->brother);
        while (!que.isEmpty())
            levelOrder(tree[que.deQueue()]->child);
    }
}

int main()
{
    int N;
    int root;

    cin >> N;
    tree = new Node*[N+10];
    bool flag[15000];
    memset(flag, 0, sizeof(flag));
    for (int i=1; i<=N; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        tree[a] = new Node(b, c);
        flag[b] = 1;
        flag[c] = 1;
    }
    for (int i=1; i<=N; ++i)
    {
        if (flag[i]==0)
        {
            root = i;
            break;
        }
    }
    preOrder(root);
    cout <<endl;
    postOrder(root);
    cout <<endl;
    levelOrder(root);
}
