#include <iostream>
#include <iomanip>
#include "linkQueue.cpp"
using namespace std;

int main()
{
    int N;
    int busNum=0, truNum=0;
    linkQueue<int> bus;
    linkQueue<int> truck;
    cin >> N;
    for (int i=0; i<N; ++i)
    {
        int type;
        cin >> type;
        if (type==0) //bus
        {
            ++busNum;
            int time;
            cin >> time;
            bus.enQueue(time);
        }
        else //truck
        {
            ++truNum;
            int time;
            cin >> time;
            truck.enQueue(time);
        }
    }
    int cnt=0;
    int busTime=0, truTime=0;
    while (true)
    {
        int bus_num=0, tru_num=0;
        while (!bus.isEmpty() && bus_num<8 && bus.getHead()<=10*cnt)
        {
            busTime += 10*cnt-bus.deQueue();
            ++bus_num;
        }
        while (!truck.isEmpty() && tru_num<10-bus_num && truck.getHead()<=10*cnt)
        {
            truTime += 10*cnt-truck.deQueue();
            ++tru_num;
        }
        if (bus.isEmpty() && truck.isEmpty())
            break;
        ++cnt;
    }
    float busAverageWaitingTime=(float)busTime/busNum;
    float truAverageWaitingTime=(float)truTime/truNum;
    cout <<setprecision(3)<<std::fixed<< busAverageWaitingTime <<' '<<setprecision(3)<<std::fixed<< truAverageWaitingTime;
}
