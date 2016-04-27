#include <iostream>
#include "calc.h"
using namespace std;

calc::node *calc::create(char* &s)
{
    node *p, *root=NULL;
    Type returnType;
    int value;
    while (*s)
    {
        returnType = getToken(s, value);
        switch (returnType)
        {
            case DATA: case OPAREN:
                if (returnType==DATA)
                    p = new node(DATA, value);
                else
                    p = create(s);
                if (root==NULL)
                    root = p;
                else if (root->rchild==NULL)
                    root->rchild = p;
                else
                    root->rchild->rchild = p;
                break;
            case CPAREN: case EOL:
                return root;
            case ADD: case SUB:
                root = new node(returnType, 0, root);
                break;
            case MULTI: case DIV:
                if (root->type==DATA || root->type==MULTI || root->type==DIV)
                    root = new node(returnType, 0, root);
                else
                    root->rchild = new node(returnType, 0, root->rchild);
        }
    }
    return root;
}

calc::Type calc::getToken(char* &s, int &data)
{
    char chr;
    while (*s && *s==' ') ++s;
    if (*s>='0' && *s<='9')
    {
        data = 0;
        while (*s>='0' && *s<='9')
        {
            data = data*10+*s-'0';
            ++s;
        }
        return DATA;
    }
    if (*s=='\0')
        return EOL;
    chr = *s;
    ++s;
    switch (chr)
    {
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MULTI;
        case '/': return DIV;
        case '(': return OPAREN;
        case ')': return CPAREN;
        default: return EOL;
    }
}

int calc::result(calc::node *t)
{
    int num1, num2;
    if (t->type==DATA)
        return t->data;
    num1 = result(t->lchild);
    num2 = result(t->rchild);
    switch (t->type)
    {
        case ADD: t->data = num1+num2; break;
        case SUB: t->data = num1-num2; break;
        case MULTI: t->data = num1*num2; break;
        case DIV: t->data = num1/num2; break;
    }
    return t->data;
}
