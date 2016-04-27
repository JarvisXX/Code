#ifndef linkList_
#define linkList_
#include "list.h"

class OutOfBound{};

template <class elemType>
class linkList:public list<elemType>
{
private:
    struct node
    {
        elemType data;
        node *next;
        node(const elemType &x, node *p=NULL)
        {
            data = x;
            next = p;
        }
        node():next(NULL) {}
        ~node() {}
    };
    node *head;
public:
    linkList();
    ~linkList() {clear(); delete head;}
    int length() const;
    int search(const elemType &x) const; //if exists return index, otherwise return -1
    elemType visit(int i) const;
    void insert(int i, const elemType &x);
    void remove(int i);
    void clear();
    void traverse() const;
};
#endif
