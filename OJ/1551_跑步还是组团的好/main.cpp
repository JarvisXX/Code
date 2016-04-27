#include <iostream>
#include "linkStack.cpp"
using namespace std;

int main()
{
    linkStack<int> pos;
    linkStack<int> speed;
    int N;
    int P, V;

    cin >> N;
    for (int i=0; i<N; ++i)
    {
        cin >> P >> V;
        if (speed.isEmpty())
        {
            pos.push(P);
            speed.push(V);
        }
        else
        {
            if (P==pos.getTop())
            {
                if (V<speed.getTop())
                {
                    pos.pop();
                    speed.pop();
                    pos.push(P);
                    speed.push(V);
                }
                else
                    continue;
            }
            else
            {
                while (!speed.isEmpty() && V<speed.getTop())
                {
                    pos.pop();
                    speed.pop();
                }
                pos.push(P);
                speed.push(V);
            }
        }
    }
    int cnt=0;
    while (!speed.isEmpty())
    {
        speed.pop();
        ++cnt;
    }
    cout << cnt;
}
