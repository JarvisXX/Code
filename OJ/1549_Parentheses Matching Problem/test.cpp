#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

template <class elemType>
class stack
{
public:
    virtual bool isEmpty() const = 0;
    virtual void push(const elemType &x) = 0;
    virtual elemType getTop() const = 0;
    virtual elemType pop() = 0;
    virtual ~stack() {}
};

template <class elemType>
class linkStack:public stack<elemType>
{
private:
    struct node
    {
        elemType data;
        node *next;
        node (const elemType &x, node *N=NULL)
        {
            data = x;
            next = N;
        }
        node():next(NULL) {}
        ~node() {}
    };
    node *top;
public:
    linkStack();
    ~linkStack();
    bool isEmpty() const;
    elemType getTop() const;
    elemType pop();
    void push(const elemType &x);
};

template <class elemType>
linkStack<elemType>::linkStack()
{
    top = NULL;
}

template <class elemType>
linkStack<elemType>::~linkStack()
{
    node *tmp;
    while (top!=NULL)
    {
        tmp = top;
        top = top->next;
        delete tmp;
    }
}

template <class elemType>
bool linkStack<elemType>::isEmpty() const
{
    return top==NULL;
}

template <class elemType>
elemType linkStack<elemType>::getTop() const
{
    if (isEmpty())
    {
        cout << "The stack is empty.";
        exit(0);
    }
    return top->data;
}

template <class elemType>
elemType linkStack<elemType>::pop()
{
    if (isEmpty())
    {
        cout << "The stack is empty.";
        exit(0);
    }
    node *tmp=top;
    elemType x=top->data;
    top = top->next;
    delete tmp;
    return x;
}

template <class elemType>
void linkStack<elemType>::push(const elemType &x)
{
    node *tmp=new node(x, top);
    top = tmp;
}

int main()
{
    linkStack<char> op;
    linkStack<int> pos;
    char* input=new char [110];
    char* result=new char [110];
    int length;

    cin.getline(input, 110);
    length = strlen(input);
    for (int i=0; i<length; ++i)
    {
        if (input[i]=='(')
        {
            op.push(input[i]);
            pos.push(i);
        }
        if (input[i]==')')
        {
            if (!op.isEmpty() && op.getTop()=='(')
            {
                op.pop();
                pos.pop();
            }
            else
            {
                op.push(input[i]);
                pos.push(i);
            }
        }
        result[i] = ' ';
    }
    result[length] = '\0';
    while (!op.isEmpty())
    {
        char chr=op.pop();
        int num=pos.pop();
        switch(chr)
        {
            case '(': result[num] = '$'; break;
            case ')': result[num] = '?';
        }
    }
    cout << input <<endl;
    cout << result;
}
