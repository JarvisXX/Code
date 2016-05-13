#include <iostream>
#include "linkQueue.cpp"
using namespace std;

template <class T>
class AVLT{
private:
	struct AVLNode{
		AVLNode* _left;
		AVLNode* _right;
		T _data;
		int _ht;
		AVLNode():_left(NULL), _right(NULL), _ht(0){}
		AVLNode(const T &x):_left(NULL), _right(NULL), _data(x), _ht(0){}
		AVLNode(const T &x, AVLNode* l, AVLNode* r, int h = 0):
			_left(l), _right(r), _data(x), _ht(h){}
	};
	AVLNode* _root;
	void clear_(AVLNode* &rt);
	void insert_(const T &x, AVLNode* &rt);
	bool remove_(const T &x, AVLNode* &rt);
	int height(AVLNode* rt) const { return rt ? rt->_ht : -1; }
	int getMaxH(AVLNode* rt) const { return max(height(rt->_left), height(rt->_right)); }
	void LL(AVLNode* &rt);
	void LR(AVLNode* &rt);
	void RL(AVLNode* &rt);
	void RR(AVLNode* &rt);
public:
	AVLT():_root(NULL){}
	~AVLT() { clear_(_root); }
	bool find(const T &x) const;
	void insert(const T &x) {insert_(x, _root); }
	void remove(const T &x) {remove_(x, _root); }
	void levelOrder() const;
};

template <class T>
void AVLT<T>::clear_(AVLNode* &rt)
{
	if (!rt) return;
	clear_(rt->_left);
	clear_(rt->_right);
	delete rt;
}

template <class T>
void AVLT<T>::insert_(const T &x, AVLNode* &rt)
{
	if (!rt) rt = new AVLNode(x);
	else if (rt->_data > x)
	{
		insert_(x, rt->_left);
		if (height(rt->_left) - height(rt->_right) == 2)
		{
			if (x < rt->_left->_data)
				LL(rt);
			else
				LR(rt);
		}
	}
	else if (rt->_data < x)
	{
		insert_(x, rt->_right);
		if (height(rt->_right) - height(rt->_left) == 2)
		{
			if (x > rt->_right->_data)
				RR(rt);
			else
				RL(rt);
		}
	}
	rt->_ht = getMaxH(rt) + 1;
}

template <class T>
bool AVLT<T>::remove_(const T &x, AVLNode* &rt)
{
    //cout <<"fuck"<< rt->_data<<endl;
	bool stop = false;
	int del_subtree;
	enum LeftOrRight { LEFT = 1, RIGHT = 2};
	if (!rt)
	{
	    cout<<"damn";
	    return true;
	}
	if (x < rt->_data)
	{
		stop = remove_(x, rt->_left);
		del_subtree = LEFT;
	}
	else if (x > rt->_data)
	{
		stop = remove_(x, rt->_right);
		del_subtree = RIGHT;
	}
	else
	{
		if (rt->_left && rt->_right)
		{
			AVLNode* tmp = rt->_right;
			while (tmp->_left)
				tmp = tmp->_left;
			rt->_data = tmp->_data;
			stop = remove_(rt->_data, rt->_right);
			del_subtree = RIGHT;
		}
		else
		{
			AVLNode* out = rt;
			rt = (rt->_left) ? rt->_left : rt->_right;
			delete out;
			return false;
		}
	}

	if (stop) return true;

	int h_dif_before;
	enum DEG_BLANCE { OTHER_GREAT = -1, BLANCE = 0, CUR_GREAT = 1};
	switch(del_subtree)
	{
		case LEFT:
			h_dif_before = height(rt->_left) - height(rt->_right) + 1;
			switch(h_dif_before)
			{
				case BLANCE: return true;
				case CUR_GREAT: return false; //???
				case OTHER_GREAT:
					int right_h_dif_before = height(rt->_right->_left) - height(rt->_right->_right);
					switch(right_h_dif_before)
					{
						case BLANCE: RR(rt); return true;
						case OTHER_GREAT: RR(rt); return false;
						case CUR_GREAT: RL(rt); return false;
					}
			}
		case RIGHT:
			h_dif_before = height(rt->_right) - height(rt->_left) + 1;
			switch(h_dif_before)
			{
				case BLANCE: return true;
				case CUR_GREAT: return false;
				case OTHER_GREAT:
					int left_h_dif_before = height(rt->_right->_left) - height(rt->_right->_right);//???
					switch(left_h_dif_before)
					{
						case BLANCE: LL(rt); return true;
						case CUR_GREAT: LL(rt); return false;
						case OTHER_GREAT: LR(rt); return false;
					}
			}
		//default:return false;
	}
}

template <class T>
void AVLT<T>::levelOrder() const
{
    cout << "\nLevel Order: ";
    linkQueue<AVLNode *> que;
    que.enQueue(_root);
    while(!que.isEmpty())
    {
        AVLNode *tmp=que.deQueue();
        cout << tmp->_data <<' '<<"h:"<<tmp->_ht<<", ";
        if (tmp->_left!=NULL)
            que.enQueue(tmp->_left);
        if (tmp->_right!=NULL)
            que.enQueue(tmp->_right);
    }
}


template <class T>
void AVLT<T>::LL(AVLNode* &rt)
{
	AVLNode* up = rt->_left;
	rt->_left = up->_right;
	up->_right = rt;
	rt->_ht = getMaxH(rt) + 1;
	up->_ht = max(height(up->_left), height(rt)) + 1;
	rt = up;
}

template <class T>
void AVLT<T>::LR(AVLNode* &rt)
{
	RR(rt->_left);
	LL(rt);
}

template <class T>
void AVLT<T>::RL(AVLNode* &rt)
{
	LL(rt->_right);
	RR(rt);
}

template <class T>
void AVLT<T>::RR(AVLNode* &rt)
{
	AVLNode* up = rt->_right;
	rt->_right = up->_left;
	up->_left = rt;
	rt->_ht = getMaxH(rt) + 1;
	up->_ht = max(height(up->_right), height(rt)) + 1;
	rt = up;
}

template <class T>
bool AVLT<T>::find(const T &x) const
{
	AVLNode* tmp = _root;
	while (tmp)
	{
		if (tmp->_data == x)
			return true;
		else if (tmp->_data < x)
			tmp = tmp->_right;
		else
			tmp = tmp->_left;
	}
	return false;
}

int main()
{
	int a[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
	int b,c,d;
	b = 2;
	c = 3;
	d = 21;
	AVLT<int> tree;
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
