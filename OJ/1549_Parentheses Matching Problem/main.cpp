#include <iostream>
#include <cstring>
#include "linkStack.cpp"
using namespace std;

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
