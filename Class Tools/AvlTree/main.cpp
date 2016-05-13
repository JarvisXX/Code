#include <iostream>
#include "AvlTree.cpp"
using namespace std;

int main()
{
	int a[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
	int b,c,d;
	b = 2;
	c = 3;
	d = 21;
	AvlTree<int> tree;
	//cout<<"build suc!"<<endl;
	for (int i = 0; i < 17; ++i)
	{
		tree.insert(a[i]);
		//cout<<"init suc!"<<endl;
	}
	tree.levelOrder();
	cout << endl << "find "<<b<<" is " << (tree.find(b)?"true":"false") << endl;
	tree.remove(b);
	cout << "after delete "<<b<<", find "<<b<<" is " << (tree.find(b)?"true":"false") << endl;
    tree.levelOrder();

	cout << "find "<<c<<" is " << (tree.find(c)?"true":"false") << endl;
	tree.remove(c);
	cout << "after delete "<<c<<", find "<<c<<" is " << (tree.find(c)?"true":"false") << endl;


	cout << "find "<<d<<" is " << (tree.find(d)?"true":"false") << endl;
	tree.remove(d);
	cout << "after delete "<<d<<", find "<<d<<" is " << (tree.find(d)?"true":"false") << endl;
	return 0;
}
