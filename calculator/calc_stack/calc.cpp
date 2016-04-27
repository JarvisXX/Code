#include <iostream>
#include <cstring>
#include <cmath>
#include "calc.h"
using namespace std;

calc::calc(char *s)
{
    expression = new char[strlen(s) + 1];
    strcpy(expression, s);
}

void calc::BinaryOp(token op, seqStack<int> &dataStack)
{
    int num1, num2;
    if (dataStack.isEmpty())
    {
        cerr << "Error";
        exit(1);
    }
    else
        num2 = dataStack.pop();
    if (dataStack.isEmpty())
    {
        cerr << "Error";
        exit(1);
    }
    else
        num1 = dataStack.pop();
    switch(op)
    {
        case ADD: dataStack.push(num1+num2); break;
        case SUB: dataStack.push(num1-num2); break;
        case MULTI: dataStack.push(num1*num2); break;
        case DIV:
            if (num2==0)
            {
                cerr << "Error";
                exit(1);
            }
            dataStack.push(num1/num2); break;
        case EXP: dataStack.push(pow(num1, num2));
    }
}

calc::token calc::getOp(int &value)
{
    while (*expression)
    {
        while (*expression && *expression==' ') ++expression;
        if (*expression>='0' && *expression<='9')
        {
            value = 0;
            while (*expression>='0' && *expression<='9')
            {
                value = value*10+*expression-'0';
                ++expression;
            }
            return VALUE;
        }
        switch (*expression)
        {
            case '(': ++expression; return OPAREN;
            case ')': ++expression; return CPAREN;
            case '+': ++expression; return ADD;
            case '-': ++expression; return SUB;
            case '*': ++expression; return MULTI;
            case '/': ++expression; return DIV;
            case '^': ++expression; return EXP;
        }
    }
    return EOL;
}

int calc::result()
{
    token lastOp, topOp;
    int result_value, CurrentValue;
    seqStack<token> opStack;
    seqStack<int> dataStack;
    char *str=expression;
    while(true)
    {
        lastOp = getOp(CurrentValue);
        if (lastOp==EOL) break;
        switch(lastOp)
        {
            case VALUE: dataStack.push(CurrentValue); break;
            case OPAREN: opStack.push(OPAREN); break;
            case CPAREN:
                if (opStack.isEmpty())
                {
                    cerr << "Error" << endl;
                    exit(1);
                }
                while (!opStack.isEmpty() && (topOp=opStack.pop())!=OPAREN)
                    BinaryOp(topOp, dataStack);
                if (topOp!=OPAREN)
                {
                    cerr << "Error" << endl;
                    exit(1);
                }
                break;
            case ADD: case SUB:
                while (!opStack.isEmpty() && opStack.getTop()!=OPAREN)
                    BinaryOp(opStack.pop(), dataStack);
                opStack.push(lastOp);
                break;
            case MULTI: case DIV:
                while (!opStack.isEmpty() && opStack.getTop()>=MULTI)
                    BinaryOp(opStack.pop(), dataStack);
                opStack.push(lastOp);
                break;
            case EXP: opStack.push(EXP);
        }
    }
    while (!opStack.isEmpty())
        BinaryOp(opStack.pop(), dataStack);
    if (dataStack.isEmpty())
    {
        cout << "Error";
        return 0;
    }
    result_value = dataStack.pop();
    if (!dataStack.isEmpty())
    {
        cout << "Error";
        return 0;
    }
    expression = str;
    return result_value;
}

calc calc::operator=(char *s)
{
    expression = new char[strlen(s) + 1];
    strcpy(expression, s);
}
