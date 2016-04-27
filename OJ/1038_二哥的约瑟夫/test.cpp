#include<iostream>
using namespace std;

struct linkNode
{	int data;
	linkNode *next;
};

int main()
{	int M;
	int qwer;
	linkNode *head, *p, *q;

	cin >> M;
	qwer = M;
	head = p = new linkNode;
	p->data = 1;
	for (int i=2; i<=M; ++i)
	{	q = new linkNode;
		q->data = i;
		p->next = q;
		p = q;
	}
	p->next = head;

	q = head;
	for (int i=1; i<M; ++i)
	{	int num;
		cin >> num;
		num = num % qwer;
		if (num==0)
			num = qwer;
		for (int j=0; j<num-1; ++j)
		{	p = q;
			q = q->next;
		}
		p->next = q->next;
		delete q;
		--qwer;
		q = p->next;
		if (p == q)
			break;
	}

	/*cout << "Á´±íÄÚÈÝ£º\n";
	p = head;
	while (p!=NULL)
	{	cout << p->data << endl;
		p = p->next;
		char a;
		cin >> a;
	}*/

	cout << p->data;
}
