#ifndef simulator_
#define simulator_
class simulator
{
    int noOfServer;
    int arrivalLow;
    int arrivalHigh;
    int serviceTimeLow;
    int serviceTimeHigh;
    int customNum;

    struct eventT
    {
        int time;
        int type;
        bool operator<(const eventT &e) const
        {
            return time<e.time;
        }
    };
public:
    simulator();
    int avgWaitTime();
};
#endif
