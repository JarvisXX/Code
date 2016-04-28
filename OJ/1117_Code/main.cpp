#include <iostream>
#include <cstring>
#include "linkStack.cpp"
#include "priorityQueue.cpp"
using namespace std;

int main()
{
    char ch;
    int num=0;
    int N=0;
    int root=0;
    linkStack<int> stack;
    priorityQueue<int> tree;
    int father[100010];
    int neighbor[100010];

    memset(father, 0, sizeof(father));
    memset(neighbor, 0, sizeof(neighbor));
    while (cin>>ch)
    {
        if (ch==' ')
            continue;
        else if (ch=='(')
        {
            if (num!=0)
            {
                stack.push(num);
                if (root==0)
                    root = num;
                N = (N>num?N:num);
                num = 0;
            }
        }
        else if (ch==')')
        {
            if (num!=0)
            {
                father[num] = stack.getTop();
                ++neighbor[num];
                ++neighbor[stack.getTop()];
                N = (N>num?N:num);
                num = 0;
            }
            else
            {
                int leaf=stack.pop();
                if (!stack.isEmpty())
                {
                    father[leaf] = stack.getTop();
                    ++neighbor[leaf];
                    ++neighbor[stack.getTop()];
                }
            }
        }
        else
            num = num*10+ch-'0';
    }

    for (int i=1; i<=N; ++i)
        if (neighbor[i]==1)
            tree.enQueue(i);

    for (int i=0; i<N-1; ++i)
    {
        int out=tree.deQueue();
        if (out==root)
        {
            for (int j=1; j<=N; ++j)
            {
                if (father[j]==root && neighbor[j]!=0)
                {
                    cout << j <<' ';
                    --neighbor[root];
                    --neighbor[j];
                    if (neighbor[j]==1)
                        tree.enQueue(j);
                    root = j;
                    break;
                }
            }
        }
        else
        {
            cout << father[out] <<' ';
            --neighbor[out];
            --neighbor[father[out]];
            if (neighbor[father[out]]==1)
                tree.enQueue(father[out]);
        }
    }
}
