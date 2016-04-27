#include <iostream>
using namespace std;

template <class elemType>
class list
{
public:
    virtual int length() const = 0;
    virtual int search(const elemType &x) const = 0;
    virtual elemType visit(int i) const = 0;
    virtual void insert(int i, const elemType &x) = 0;
    virtual void remove(int i) = 0;
    virtual void clear() = 0;
    virtual void traverse() const = 0;
    virtual ~list() {}
};

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

template <class elemType>
linkList<elemType>::linkList()
{
    head = new node();
}

template <class elemType>
int linkList<elemType>::length() const
{
    int len=0;
    node *p=head->next;
    while (p!=NULL)
    {
        ++len;
        p = p->next;
    }
    return len;
}

template <class elemType>
int linkList<elemType>::search(const elemType &x) const
{
    int num=0;
    node *p=head->next;
    while (p!=NULL && p->data!=x)
    {
        ++num;
        p = p->next;
    }
    if (p==NULL) return -1;
    return num;
}

template <class elemType>
elemType linkList<elemType>::visit(int i) const
{
    if (i<0) throw OutOfBound();
    node *p=head->next;
    for (int j=0; p!=NULL && j<i; ++j) p = p->next;
    if (p==NULL) throw OutOfBound();
    return p->data;
}

template <class elemType>
void linkList<elemType>::insert(int i, const elemType &x)
{
    if (i<0) throw OutOfBound();
    node *tmp, *p=head;
    for (int j=0; p!=NULL && j<i; ++j) p = p->next;
    if (p==NULL) throw OutOfBound();
    tmp = new node(x, p->next);
    p->next = tmp;
}

template <class elemType>
void linkList<elemType>::remove(int i)
{
    if (i<0) throw OutOfBound();
    node *tmp, *p=head;
    for (int j=0; p!=NULL && j<i; ++j) p = p->next;
    if (p==NULL || p->next==NULL) throw OutOfBound();
    tmp = p->next;
    p->next = tmp->next;
    delete tmp;
}

template <class elemType>
void linkList<elemType>::clear()
{
    node *p=head->next;
    while (p!=NULL)
    {
        node *q=p;
        p = p->next;
        delete q;
    }
    head->next = NULL;
}

template <class elemType>
void linkList<elemType>::traverse() const
{
    node *p=head->next;
    if (p!=NULL)
    {
        cout << p->data;
        p = p->next;
    }
    while (p!=NULL)
    {
        cout << "->" << p->data;
        p = p->next;
    }
    cout << endl;
}
