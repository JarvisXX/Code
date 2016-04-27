#include <iostream>
#include "linkStack.cpp"
using namespace std;

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
