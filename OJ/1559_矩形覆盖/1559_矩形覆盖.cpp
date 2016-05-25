#include <iostream>
#include <cstring>
using namespace std;

template <class elemType>
class queue{
public: 
	virtual bool isEmpty() = 0;
	virtual void enQueue(const elemType &x) = 0;
	virtual elemType  deQueue() = 0;
	virtual elemType getHead() = 0;
	virtual ~queue() {};
 };

template <class elemType>
class linkQueue: public queue<elemType>{
private:
	struct node{
    	elemType  data;
		node *next;
  		node(const elemType &x, node *N = NULL){
  			data = x;
  			next = N;
  		}
		node():next(NULL) {}
		~node() {}
	};
	node *front, *rear;   
public:
	linkQueue(){front = rear = NULL;}
	~linkQueue();
	bool isEmpty(){return front == NULL;}
	void enQueue(const elemType &x);
	elemType deQueue();  
	elemType getHead(){return front->data;}
	elemType gettail(){return rear->data;}
};

template <class elemType>
linkQueue<elemType>::~linkQueue(){
	node *tmp;
	while(front){
		tmp = front;
		front = front->next;
		delete tmp;
	}
}

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x){
	if(!front) front = rear = new node(x);
	else{
		rear->next = new node(x);
		rear = rear->next;
	}
}

template <class elemType>
elemType linkQueue<elemType>::deQueue(){
	node *tmp = front;
	elemType res = front->data;
	front = front->next;
	delete tmp;
	if(!front) rear = NULL;
	return res;
}

int gx[502]={0};
int gy[502]={0};
int hx[502]={0};
int hy[502]={0};

struct rec{
	int xmin, ymin, xmax, ymax;
	int numG, numH;

	rec(int a, int b, int c, int d, int g=0, int h=0):
		xmin(a), ymin(b), xmax(c), ymax(d), numG(g), numH(h){}
	~rec(){}
};

void find(int indexH, int indexG, rec *&a, rec*&b, rec *&c, rec*&d){
	int axi=1000,ayi=1000,axa=0,aya=0;
	int bxi=1000,byi=1000,bxa=0,bya=0;
	int cxi=1000,cyi=1000,cxa=0,cya=0;
	int dxi=1000,dyi=1000,dxa=0,dya=0;
	for(int i=0; i<indexH; ++i){
		if(hx[i]<=a->xmax&&hx[i]>=a->xmin&&hy[i]<=a->ymax&&hy[i]>=a->ymin){
			axi=axi<hx[i]?axi:hx[i];
			ayi=ayi<hy[i]?ayi:hy[i];
			axa=axa>hx[i]?axa:hx[i];
			aya=aya>hy[i]?aya:hy[i];
			++a->numH;
		}
		if(hx[i]<=b->xmax&&hx[i]>=b->xmin&&hy[i]<=b->ymax&&hy[i]>=b->ymin){
			bxi=bxi<hx[i]?bxi:hx[i];
			byi=byi<hy[i]?byi:hy[i];
			bxa=bxa>hx[i]?bxa:hx[i];
			bya=bya>hy[i]?bya:hy[i];
			++b->numH;
		}
		if(hx[i]<=c->xmax&&hx[i]>=c->xmin&&hy[i]<=c->ymax&&hy[i]>=c->ymin){
			cxi=cxi<hx[i]?cxi:hx[i];
			cyi=cyi<hy[i]?cyi:hy[i];
			cxa=cxa>hx[i]?cxa:hx[i];
			cya=cya>hy[i]?cya:hy[i];
			++c->numH;
		}
		if(hx[i]<=d->xmax&&hx[i]>=d->xmin&&hy[i]<=d->ymax&&hy[i]>=d->ymin){
			dxi=dxi<hx[i]?dxi:hx[i];
			dyi=dyi<hy[i]?dyi:hy[i];
			dxa=dxa>hx[i]?dxa:hx[i];
			dya=dya>hy[i]?dya:hy[i];
			++d->numH;
		}
	}
	a->xmin = axi;a->ymin = ayi;a->xmax = axa;a->ymax = aya;
	b->xmin = bxi;b->ymin = byi;b->xmax = bxa;b->ymax = bya;
	c->xmin = cxi;c->ymin = cyi;c->xmax = cxa;c->ymax = cya;
	d->xmin = dxi;d->ymin = dyi;d->xmax = dxa;d->ymax = dya;
	for(int i=0; i<indexG; ++i){
		if(gx[i]<=a->xmax&&gx[i]>=a->xmin&&gy[i]<=a->ymax&&gy[i]>=a->ymin){
			++a->numG;
		}
		if(gx[i]<=b->xmax&&gx[i]>=b->xmin&&gy[i]<=b->ymax&&gy[i]>=b->ymin){
			++b->numG;
		}
		if(gx[i]<=c->xmax&&gx[i]>=c->xmin&&gy[i]<=c->ymax&&gy[i]>=c->ymin){
			++c->numG;
		}
		if(gx[i]<=d->xmax&&gx[i]>=d->xmin&&gy[i]<=d->ymax&&gy[i]>=d->ymin){
			++d->numG;
		}
	}
}

int main(){
	linkQueue<rec*> que;
	rec *tmp, *p;
	int n, xmin=1000, ymin=1000, xmax=0, ymax=0;
	int area=0, num=0, numG=0, numH=0;
	int Gx, Gy, indexG=0, indexH=0, x, y;
	char t;
	cin>>n;
	for(int i=0; i<n; ++i){
		cin>>x>>y>>t;
		
		if(t=='H'){
			hx[indexH]=x;
			hy[indexH]=y;
			xmin=xmin<hx[indexH]?xmin:hx[indexH];
			ymin=ymin<hy[indexH]?ymin:hy[indexH];
			xmax=xmax>hx[indexH]?xmax:hx[indexH];
			ymax=ymax>hy[indexH]?ymax:hy[indexH];
			++numH;
			++indexH;
		}
		else{
			gx[indexG]=x;
			gy[indexG]=y;
			++indexG;
		}
	}
	for(int i=0; i<indexG; ++i){
		if(gx[i]<=xmax&&gx[i]>=xmin&&gy[i]<=ymax&&gy[i]>=ymin){
			++numG;
		}
	}

	tmp = new rec(xmin,ymin,xmax,ymax,numG,numH);
	que.enQueue(tmp);

	while(!que.isEmpty()){
		p = que.deQueue();
		if(p->numH<num) continue;
		if(p->numG==0){
			if(p->numH>num){
				num = p->numH;
				area=(p->xmax-p->xmin)*(p->ymax-p->ymin);
			}
			else if(p->numH==num){
				area = area<=(p->xmax-p->xmin)*(p->ymax-p->ymin)? area:(p->xmax-p->xmin)*(p->ymax-p->ymin);
			}
		}
		else{
			for(int i=0; i<indexG; ++i){
				if(gx[i]<=p->xmax&&gx[i]>=p->xmin&&gy[i]<=p->ymax&&gy[i]>=p->ymin){
					Gx=gx[i];
					Gy=gy[i];
					break;
				}
			}

			rec *tmp1 = new rec(Gx+1,p->ymin,p->xmax,p->ymax);
			rec *tmp2 = new rec(p->xmin,Gy+1,p->xmax,p->ymax);
			rec *tmp3 = new rec(p->xmin,p->ymin,Gx-1,p->ymax);
			rec *tmp4 = new rec(p->xmin,p->ymin,p->xmax,Gy-1);
			find(indexH,indexG,tmp1,tmp2,tmp3,tmp4);

			que.enQueue(tmp1);
			que.enQueue(tmp2);
			que.enQueue(tmp3);
			que.enQueue(tmp4);
		}
	}

	cout<<num<<"   "<<area<<endl;

	return 0;
}
