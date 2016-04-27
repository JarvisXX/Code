#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
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
    node *tmp = new node(x, top);
    top = tmp;
}

int scale(char chr)
{
    if (int(chr)>=48 && int(chr)<=57)
        return 0;
    else
    {
        switch(chr)
        {
            case '#': return 0;
            case ')': return 1;
            case '+':
            case '-': return 2;
            case '*':
            case '/': return 3;
            case '(': return 4;
        }
    }
}

char* charAdd(char a, char* b)
{
    char* c=new char [strlen(b)+10];
    c[0]=a;
    c[1]='\0';
    strcat(c, b);
    return c;
}

char* strrev(char* str)
{
    int length=strlen(str);
    char *tmp=new char[length+10];
    for (int i=0; i<length; ++i)
        tmp[i] = str[length-i-1];
    tmp[length]='\0';
    return tmp;
}

void calc(linkStack<int> &num, char op)
{
    switch(op)
    {
        case '+':
        {
            int num_1=num.pop();
            int num_2=num.pop();
            num.push(num_1+num_2);
            break;
        }
        case '-':
        {
            int num_1=num.pop();
            int num_2=num.pop();
            num.push(num_1-num_2);
            break;
        }
        case '*':
        {
            int num_1=num.pop();
            int num_2=num.pop();
            num.push(num_1*num_2);
            break;
        }
        case '/':
        {
            int num_1=num.pop();
            int num_2=num.pop();
            num.push(num_1/num_2);
            break;
        }
    }
}

char* PN(char* expression, int &result_num)
{
    int length=strlen(expression);
    char* new_expression=new char[length+10];
    char* result=new char[length+10];
    new_expression=strrev(expression);
    strcpy(result, "");
    linkStack<char> stack;
    linkStack<int> num;
    stack.push('#');
    int flag=0;
    while (strlen(new_expression)!=0)
    {
        char chr=new_expression[0];
        if (chr==' ')
        {
            ++new_expression;
            continue;
        }
        int index=scale(chr);
        switch(index)
        {
            case 0:
            {
                if (flag)
                {
                    result=charAdd(chr, result);
                    int tmp=num.pop();
                    tmp += (chr-48)*pow(10,flag);
                    num.push(tmp);
                    flag += 1;
                }
                else
                {
                    result=charAdd(' ', result);
                    result=charAdd(chr, result);
                    num.push(chr-48);
                    flag += 1;
                }
                break;

            }
            case 1:
            {
                stack.push(chr);
                flag = 0;
                break;
            }
            case 2:
            {
                if (index>=scale(stack.getTop())) stack.push(chr);
                else
                {
                    char op=stack.pop();
                    result=charAdd(' ', result);
                    result=charAdd(op, result);
                    calc(num, op);
                    stack.push(chr);
                }
                flag = 0;
                break;
            }
            case 3:
            {
                if (index>=scale(stack.getTop())) stack.push(chr);
                else
                {
                    char op=stack.pop();
                    result=charAdd(' ', result);
                    result=charAdd(op, result);
                    calc(num, op);
                    stack.push(chr);
                }
                flag = 0;
                break;
            }
            case 4:
            {
                while (stack.getTop()!=')')
                {
                    char op=stack.pop();
                    result=charAdd(' ', result);
                    result=charAdd(op, result);
                    calc(num, op);
                }
                stack.pop();
                flag = 0;
                break;
            }
        }
        ++new_expression;
    }
    while (stack.getTop()!='#')
    {
        char op=stack.pop();
        result=charAdd(' ', result);
        result=charAdd(op, result);
        calc(num, op);
    }
    result_num=num.getTop();
    return result;
}

int main()
{
    char* input=new char[1000];
    cin.getline(input,1000);
    char* output=new char[1000];
    int result=0;
    output = PN(input, result);
    cout << output <<endl;
    cout << result;
}
