#include <iostream>
#include "linkList.h"
using namespace std;

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
