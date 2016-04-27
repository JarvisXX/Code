#include <iostream>
#include <cstdlib>
#include <cstring>
#include "linkQueue.cpp"
using namespace std;

struct Node
{
    int weight;
    int child;
    int brother;
    Node(int w, int c, int b):weight(w), child(c), brother(b) {}
    ~Node() {}
}**tree;

void preOrder(int t)
{
    if (t!=0)
    {
        cout << tree[t]->weight <<' ';
        preOrder(tree[t]->child);
        preOrder(tree[t]->brother);
    }
}

void postOrder(int t)
{
    if (t!=0)
    {
        postOrder(tree[t]->child);
        cout << tree[t]->weight <<' ';
        postOrder(tree[t]->brother);
    }
}
linkQueue<int> que;
void levelOrder(int t)
{
    if (t!=0)
    {
        cout << tree[t]->weight <<' ';
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
    bool flag[100010];
    memset(flag, 0, sizeof(flag));
    for (int i=1; i<=N; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        tree[i] = new Node(c, a, b);
        flag[a] = 1;
        flag[b] = 1;
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
