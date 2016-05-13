#ifndef cHT
#define cHT
#include "hashTable.h"

template <class Type>
class closeHashTable:public hashTable<Type>
{
private:
    struct node
    {
        Type data;
        int state; // 0-empty 1-active 2-deleted
        node() {state=0;}
    };
    node *array;
    int size;
public:
    closeHashTable(int length=101, int (*f)(const Type &x)=defaultKey);
    ~closeHashTable() {delete [] array;}
    bool find(const Type &x) const;
    bool insert(const Type &x);
    bool remove(const Type &x);
    void rehash();
};
#endif
