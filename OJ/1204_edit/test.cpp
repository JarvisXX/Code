#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

void list(int l);
void ins(int l);
void del(int l);
void quit();

string txt[100];

int main()
{	string order;
	//freopen("1204.txt","r",stdin);

	int l=0;
	do
	{	getline(cin, txt[l]);
		++l;
	} while(txt[l-1]!="******");
	--l;

	do
	{	cin >> order;
		if (order[0]=='l')
			list(l);
		else if (order[0]=='i')
			ins(l);
		else if (order[0]=='d')
			del(l);
		else
			quit();
	} while(order!="quit");
	return 0;
}

void list(int l)
{	int a, b;
	cin >> a >> b;
	if (a>b || a<=0 || b<=0 || a>l || b>l)
	{	cout << "Error!" << endl;
		return;
	}
	for (int i=a-1; i<b; ++i)
		cout << txt[i] << endl;
}

void ins(int l)
{	int a, b;
	string nstr, istr;
	cin >> a >> b;
	getline(cin,istr);
	istr = istr.substr(1, istr.length()-1);
	if (a<=0 || b<=0 || a>l || b>txt[a-1].length()+1)
	{	cout << "Error!" << endl;
		return;
	}
	nstr = txt[a-1].substr(0, b-1) + istr + txt[a-1].substr(b-1, txt[a-1].length()-b+1);
	txt[a-1] = nstr;
}

void del(int l)
{	int a, b, c;
	string nstr;
	cin >> a >> b >> c;
	if (a<=0 || b<=0 || a>l || b>txt[a-1].length() || c>txt[a-1].length()-b+1)
	{	cout << "Error!" << endl;
		return;
	}
	nstr = txt[a-1].substr(0, b-1) + txt[a-1].substr(b+c-1, txt[a-1].length()-b-c+1);
	txt[a-1] = nstr;
}

void quit()
{	for (int i=0; txt[i]!="******"; ++i)
		cout << txt[i] << endl;
}
