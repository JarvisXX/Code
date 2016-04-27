#include <iostream>
#include <cstdlib>
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
    linkStack<int> dam;
    int n;
    int height[1010];
    int go=0;
    int num=0;
    char chr;
    int result=0;

    cin >> n;
    while (true)
    {
        cin >> chr;
        if (chr=='[')
            continue;
        else if (chr==']')
        {
            height[go++] = num;
            break;
        }
        else if (chr==',')
        {
            height[go++] = num;
            num = 0;
        }
        else
            num = num*10+chr-'0';
    }

    for (int i=0; i<n; ++i)
    {
        if (dam.isEmpty())
            dam.push(i);
        else
        {
            int currentH=height[i];
            int lastPos=dam.pop();
            int lastH=height[lastPos];
            if (currentH<lastH)
            {
                dam.push(lastPos);
                dam.push(i);
            }
            else if (currentH==lastH)
                dam.push(i);
            else
            {
                if (dam.isEmpty())
                    dam.push(i);
                else
                {
                    while (!dam.isEmpty() && height[dam.getTop()]<=currentH)
                    {
                        int pos=dam.pop();
                        result += (height[pos]-lastH)*(i-pos-1);
                        lastH = height[pos];
                    }
                    if (!dam.isEmpty())
                        result += (currentH-lastH)*(i-dam.getTop()-1);
                    dam.push(i);
                }
            }
        }
    }
    cout << result;
}
