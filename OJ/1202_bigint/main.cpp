#include <iostream>
#include <cstdio>
#include "B_num.cpp"
using namespace std;

int main()
{
    string a_input, b_input;
    cin >> a_input;
    cin >> b_input;
    B_num a(a_input);
    B_num b(b_input);
    a.add(b).print();
}
