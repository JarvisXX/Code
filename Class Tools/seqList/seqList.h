#ifndef seqList_
#define seqList_
#include "list.h"

class OutOfBound{};

class IllegalSize{};

template <class elemType>
class seqList:public list<elemType>
{
private:
    elemType *data;
    int currentLength;
    int maxSize;
    void doubleSpace();
public:
    seqList(int initSize=10);
    ~seqList() {delete [] data;}
    int length() const;
    int search(const elemType &x) const; //if exists return index, otherwise return -1
    elemType visit(int i) const;
    void insert(int i, const elemType &x);
    void remove(int i);
    void clear();
    void traverse() const;
};
#endif
