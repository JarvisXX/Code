//calc.h
#ifndef calc_
#define calc_
#include "seqStack.cpp"

class calc
{
private:
    char *expression;
    enum token {OPAREN, ADD, SUB, MULTI, DIV,
                EXP, CPAREN, VALUE, EOL};
    void BinaryOp(token op, seqStack<int> &dataStack);
    token getOp(int &value);
public:
    calc(char *s);
    ~calc() {delete expression;}
    calc operator=(char *s);
    int result();
};
#endif
