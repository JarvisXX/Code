#include <iostream>
#include "calc.cpp"
using namespace std;

int main()
{
    calc exp(" 2*3+(1 * 2*3+6*6) * (2+3)/5 + 2/2");
    cout << exp.result() <<endl;
    return 0;
}
