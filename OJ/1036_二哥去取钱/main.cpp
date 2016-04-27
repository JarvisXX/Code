#include <iostream>
#include "linkQueue.cpp"
using namespace std;

void OldMethod(int N, int line[], int &total_time, int &last_one)
{
    int quo=N/3;
    int t0=0, t1=0, t2=0;
    switch(N%3)
    {
        case 0:
        {
            for (int i=0; i<N; ++i)
            {
                switch(i%3)
                {
                    case 0: total_time += t0; t0 += line[i]; break;
                    case 1: total_time += t1; t1 += line[i]; break;
                    case 2: total_time += t2; t2 += line[i]; break;
                }
            }
            break;
        }
        case 1:
        {
            for (int i=0; i<N; ++i)
            {
                switch(i%3)
                {
                    case 0: total_time += t0; t0 += line[i]; break;
                    case 1: total_time += t1; t1 += line[i]; break;
                    case 2: total_time += t2; t2 += line[i]; break;
                }
            }
            break;
        }
        case 2:
        {
            for (int i=0; i<N; ++i)
            {
                switch(i%3)
                {
                    case 0: total_time += t0; t0 += line[i]; break;
                    case 1: total_time += t1; t1 += line[i]; break;
                    case 2: total_time += t2; t2 += line[i]; break;
                }
            }
            break;
        }
    }
    last_one = ((t0>t1?t0:t1)>t2?(t0>t1?t0:t1):t2);
}

void NewMethod(int N, linkQueue<int> &que, int &total_time, int &last_one)
{
    int t0=0, t1=0, t2=0;
    while(!que.isEmpty())
    {
        if (t1<=t2)
        {
            if (t0<=t1)
            {
                //-> t0
                total_time += t0;
                t0 += que.deQueue();
            }
            else
            {
                //-> t1
                total_time += t1;
                t1 += que.deQueue();
            }
        }
        else
        {
            if (t0<=t2)
            {
                //-> t0
                total_time += t0;
                t0 += que.deQueue();
            }
            else
            {
                //-> t2
                total_time += t2;
                t2 += que.deQueue();
            }
        }
    }
    last_one = ((t0>t1?t0:t1)>t2?(t0>t1?t0:t1):t2);
}

int main()
{
    int N;
    int line[100010];
    linkQueue<int> que;
    int total_timeOld=0, last_oneOld=0, total_timeNew=0, last_oneNew=0;
    cin >> N;
    for (int i=0; i<N; ++i)
    {
        int input;
        cin >> input;
        line[i] = input;
        que.enQueue(input);
    }
    OldMethod(N, line, total_timeOld, last_oneOld);
    NewMethod(N, que, total_timeNew, last_oneNew);
    cout << total_timeOld <<' '<< last_oneOld <<endl;
    cout << total_timeNew <<' '<< last_oneNew;
}
