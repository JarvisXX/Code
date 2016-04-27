#include <iostream>
#include <cstring>
#include "linkStack.cpp"
using namespace std;

int scale(char chr)
{
    if (int(chr)>=48 && int(chr)<=57)
        return 0;
    else
    {
        switch(chr)
        {
            case '#': return 0;
            case '(': return 1;
            case '+':
            case '-': return 2;
            case '*':
            case '/': return 3;
            case ')': return 4;
        }
    }
}

char* charAdd(char* a, char b)
{
    char* c=new char [2];
    c[0]=b;
    c[1]='\0';
    strcat(a, c);
    return a;
}

char* RPN(char* expression)
{
    char* result=new char[strlen(expression)+10];
    strcpy(result, "");
    linkStack<char> stack;
    stack.push('#');
    while (strlen(expression)!=0)
    {
        char chr=expression[0];
        int index=scale(chr);
        switch(index)
        {
            case 0: charAdd(result, chr); break;
            case 1: stack.push(chr); break;
            case 2:
            {
                if (index>scale(stack.getTop())) stack.push(chr);
                else
                {
                    charAdd(result, stack.pop());
                    stack.push(chr);
                }
                break;
            }
            case 3:
            {
                if (index>scale(stack.getTop())) stack.push(chr);
                else
                {
                    charAdd(result, stack.pop());
                    stack.push(chr);
                }
                break;
            }
            case 4:
            {
                while (stack.getTop()!='(') charAdd(result, stack.pop());
                stack.pop();
                break;
            }
        }
        ++expression;
    }
    while (stack.getTop()!='#') charAdd(result, stack.pop());
    return result;
}

int main()
{
    char* input=new char[100];
    cin >> input;
    cout << RPN(input);
}
