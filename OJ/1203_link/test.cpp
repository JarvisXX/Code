#include <iostream>
using namespace std;

template <class elemType>
class list
{
public:
    virtual void insert(int i, const elemType &x) = 0;
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
    void insert(int i, const elemType &x);
    void clear();
    void traverse() const;
    void merge(const linkList &l);
};

template <class elemType>
linkList<elemType>::linkList()
{
    head = new node();
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
        cout << " " << p->data;
        p = p->next;
    }
    cout << endl;
}

template <class elemType>
void linkList<elemType>::merge(const linkList &l)
{
    node *p=head, *q=l.head;
    q = q->next;
    while (p->next!=NULL) p = p->next;
    while (q!=NULL)
    {
        node *o=new node(q->data, NULL);
        p->next = o;
        p = o;
        q = q->next;
    }
}

int main()
{
    string type;
    int n, m;
    cin >> type;
    cin >> n >> m;

    if (type=="int")
    {
        linkList<int> a, b;
        for (int i=0; i<n; ++i)
        {
            int x;
            cin >> x;
            a.insert(i, x);
        }
        for (int i=0; i<m; ++i)
        {
            int x;
            cin >> x;
            b.insert(i, x);
        }
        a.merge(b);
        a.traverse();
    }
    else if (type=="char")
    {
        linkList<char> a, b;
        for (int i=0; i<n; ++i)
        {
            char x;
            cin >> x;
            a.insert(i, x);
        }
        for (int i=0; i<m; ++i)
        {
            char x;
            cin >> x;
            b.insert(i, x);
        }
        a.merge(b);
        a.traverse();
    }
    else if (type=="double")
    {
        linkList<double> a, b;
        for (int i=0; i<n; ++i)
        {
            double x;
            cin >> x;
            a.insert(i, x);
        }
        for (int i=0; i<m; ++i)
        {
            double x;
            cin >> x;
            b.insert(i, x);
        }
        a.merge(b);
        a.traverse();
    }
    else cout << "invalid input";
    return 0;
}
