#ifndef oHT
#define oHT
#include "hashTable.h"

template <class Type>
class openHashTable:public hashTable<Type>
{
private:
    struct node
    {
        Type data;
        node *next;
        node
    }
}
#endif
