#include <iostream>
#include <cstdlib>
#include <ctime>
#include "simulator.h"
#include "linkQueue.cpp"
#include "priorityQueue.cpp"
using namespace std;

simulator::simulator()
{
    cout << "�������̨����";
    cin >> noOfServer;

    cout << "�����뵽��ʱ���������½磨��С���ʱ�� �����ʱ�䣩��";
    cin >> arrivalLow >> arrivalHigh;

    cout << "���������ʱ������½磨����ʱ���½� ����ʱ���Ͻ磩��";
    cin >> serviceTimeLow >> serviceTimeHigh;

    cout << "������ģ��Ĺ˿�����";
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
