#include<iostream>
#include<cstring>
using namespace std;

int main()
{	int N;
	int ifNum, thenNum, elseNum, beginNum, endNum;
	string words;
	bool result, ifFlag;

	ifNum = thenNum = elseNum = beginNum = endNum = 0;
	result = 1;
	ifFlag = 0;

	//freopen("1206.txt", "r", stdin);
	while(cin >> words)
	{	if (words=="begin")
		{	++beginNum;
			if (ifFlag)  result = 0;
		}
		if (words=="end")
			++endNum;
		if (words=="if")
		{	++ifNum;
			ifFlag = 1;
		}
		else ifFlag = 0;
		if (words=="then")
			++thenNum;
		if (words=="else")
			++elseNum;

		if (endNum>beginNum || thenNum>ifNum || elseNum>thenNum)
			result = 0;

		if (!result)  break;
	}

	if (ifNum!=thenNum || beginNum!=endNum)
		result = 0;

	if (result)  cout << "Match!";
	else  cout << "Error!";

	return 0;
}
