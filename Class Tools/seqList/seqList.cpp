#include <iostream>
#include "seqList.h"
using namespace std;

template <class elemType>
void seqList<elemType>::doubleSpace()
{
    elemType *tmp = new elemType[maxSize*2];
    if (!tmp) throw IllegalSize();
    for (int j=0; j<currentLength; ++j)
        tmp[j] = data[j];
    delete [] data;
    data = tmp;
    maxSize = maxSize*2;
}

template <class elemType>
seqList<elemType>::seqList(int initSize)
{
    data = new elemType[initSize];
    if (!data) throw IllegalSize();
    maxSize = initSize;
    currentLength = 0;
}

template <class elemType>
int seqList<elemType>::length() const
{
    return currentLength;
}

template <class elemType>
int seqList<elemType>::search(const elemType &x) const
{
    int i;
    for (i=0; i<currentLength; ++i)
        if (data[i]==x) break;
    if (i==currentLength) return -1;
    else return i;
}

template <class elemType>
elemType seqList<elemType>::visit(int i) const
{
    if (i<0 || i>=currentLength) throw OutOfBound();
    return data[i];
}

template <class elemType>
void seqList<elemType>::insert(int i, const elemType &x)
{
    if (i>currentLength || i<0) throw OutOfBound();
    if (currentLength==maxSize)
        doubleSpace();
    for (int j=maxSize; j>i; --j)
        data[j] = data[j-1];
    data[i] = x;
    ++currentLength;
}

template <class elemType>
void seqList<elemType>::remove(int i)
{
    if (i<0 || i>=currentLength) throw OutOfBound();
    for (int j=i; j<currentLength-1; ++j)
        data[j] = data[j+1];
    --currentLength;
}

template <class elemType>
void seqList<elemType>::clear()
{
    currentLength = 0;
}

template <class elemType>
void seqList<elemType>::traverse() const
{
    cout << '[';
    if (currentLength!=0) cout << data[0];
    for (int i=1; i<currentLength; ++i)
        cout << ", " << data[i];
    cout << ']' << endl;
}
