#include <iostream>
#include "calc.cpp"
using namespace std;

int main()
{
    calc exp("5 + (1 + 3) * 6 ^ 1");
    cout << exp.result() <<endl;
    exp = "2^3^2";
    cout << exp.result() <<endl;
    return 0;
}
