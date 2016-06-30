#include <iostream>
#include <cstdlib>
#include <ctime>
#include "simulator.h"
#include "linkQueue.cpp"
#include "priorityQueue.cpp"
using namespace std;

simulator::simulator()
{
    cout << "请输入柜台数：";
    cin >> noOfServer;

    cout << "请输入到达时间间隔的上下界（最小间隔时间 最大间隔时间）：";
    cin >> arrivalLow >> arrivalHigh;

    cout << "请输入服务时间的上下界（服务时间下界 服务时间上界）：";
    cin >> serviceTimeLow >> serviceTimeHigh;

    cout << "请输入模拟的顾客数：";
    cin >> customNum;

    srand(time(NULL));
}

int simulator::avgWaitTime()
{
    int serverBusy=0;
    int currentTime;
    int totalWaitTime=0;
    linkQueue<eventT> waitQueue;
    priorityQueue<eventT> eventQueue;

    eventT currentEvent;

    int i;
    currentEvent.time = 0;
    currentEvent.type = 0;
    for (i=0; i<customNum; ++i)
    {
        currentEvent.time = arrivalLow+(arrivalHigh-arrivalLow+1)*rand()/(RAND_MAX+1);
        eventQueue.enQueue(currentEvent);
    }

    while (!eventQueue.isEmpty())
    {
        currentEvent = eventQueue.deQueue();
        currentTime = currentEvent.time;
        switch (currentEvent.type)
        {
            case 0:
                if (serverBusy!=noOfServer)
                {
                    ++serverBusy;
                    currentEvent.time += serviceTimeLow+(serviceTimeHigh-serviceTimeLow+1)*rand()/(RAND_MAX+1);
                    currentEvent.type = 1;
                    eventQueue.enQueue(currentEvent);
                }
                else
                    waitQueue.enQueue(currentEvent);
                break;
            case 1:
                if (!waitQueue.isEmpty())
                {
                    currentEvent = waitQueue.deQueue();
                    totalWaitTime += currentTime-currentEvent.time;
                    currentEvent.time = currentTime+serviceTimeLow+(serviceTimeHigh-serviceTimeLow+1)*rand()/(RAND_MAX+1);
                    currentEvent.type = 1;
                    eventQueue.enQueue(currentEvent);
                }
                else
                    --serverBusy;
        }
    }

    return totalWaitTime/customNum;
}
