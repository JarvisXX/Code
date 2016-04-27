#include <iostream>
#include <cstdio>
#include "B_num.h"
using namespace std;

B_num::B_num(string a)
{
    head = new linkNode;
    linkNode *p = new linkNode;
    head = p;
    int length = a.length();
    if (length==0)
        throw EmptyString();
    for (int i=0; i<length; ++i)
    {
        linkNode *tmp = new linkNode;
        tmp->data = int(a[length-i-1])-48;
        p->next = tmp;
        p = tmp;
    }
    p->next = NULL;
}

B_num::B_num(const B_num &b)
{
    head = new linkNode;
    head = b.head;
}

B_num B_num::add(const B_num &b)
{
    linkNode *o=new linkNode;
    linkNode *p=head;
    linkNode *q=b.head;
    linkNode *result_link=o;
    bool flag_1 = 1;
    bool flag_2 = 1;
    int carry=0;
    p = p->next;
    q = q->next;
    while (flag_1||flag_2)
    {
        linkNode *tmp = new linkNode;
        int tmp_data;
        if (flag_1&&flag_2) tmp_data = p->data + q->data + carry;
        else if (flag_1&&!flag_2) tmp_data = p->data + carry;
        else if (!flag_1&&flag_2) tmp_data = q->data + carry;
        tmp->data = tmp_data%10;
        carry = tmp_data/10;
        o->next = tmp;
        o = tmp;
        if (p->next==NULL) flag_1 = 0;
        else p = p->next;
        if (q->next==NULL) flag_2 = 0;
        else q = q->next;
        if (!flag_1&&!flag_2&&carry)
        {
            linkNode *tmp = new linkNode;
            tmp->data = carry;
            o->next = tmp;
            o = tmp;
        }
    }
    o->next = NULL;
    B_num result;
    result.head = result_link;
    return result;
}

void B_num::print() const
{
    string result="";
    linkNode *p=head;
    p = p->next;
    while(true)
    {
        result = char(p->data+48) + result;
        if (p->next==NULL) break;
        else p = p->next;
    }
    printf("%s\n", result.c_str());
}
