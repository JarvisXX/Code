#include <iostream>
using namespace std;

template <class T>
class priorityQueue{
private:
	T *array;
	int current, maxSize;
	void doubleSpace();
	void percolateDown(int hole);
	void buildHeap();

public:
	priorityQueue(int n=100):maxSize(n),current(0){
		array=new T[maxSize+1];
	}
	priorityQueue(const T data[],int size):maxSize(size+10),current(size){
		array=new T[maxSize+1];
		for(int i=1; i<=size; ++i) array[i]=data[i-1];
		buildHeap();
	}
	~priorityQueue(){delete [] array;}

	bool isEmpty(){return current==0;}
	void enQueue(const T &x);
	T deQueue();
	T getHead()const{return array[1];}


};

template <class T>
void priorityQueue<T>::doubleSpace(){
	T *tmp=array;
	maxSize*=2;
	array=new T[maxSize+1];
	for(int i=1; i<=current; ++i) array[i]=tmp[i];
	delete [] tmp;
}

template <class T>
void priorityQueue<T>::percolateDown(int hole){
	T value=array[hole];
	int i=hole;

	while(i*2<=current){
		if(i*2+1>current)
			if(value>array[2*i]){
			    array[i]=array[2*i]; array[2*i]=value;
		    }
			else break;
		else
		    if(value<=array[2*i]&&value<=array[2*i+1]) break;
		    else if(array[2*i]<array[2*i+1]){
		    	array[i]=array[2*i];
		    	array[2*i]=value;
		    	i=2*i;
			}
			else{
				array[i]=array[2*i+1];
				array[2*i+1]=value;
				i=2*i+1;
			}
	}
}

template <class T>
void priorityQueue<T>::buildHeap(){
	for(int i=current/2; i>0; --i) percolateDown(i);
}

template <class T>
void priorityQueue<T>::enQueue(const T &x){
	if(current==maxSize) doubleSpace();
	array[++current]=x;
	int i=current;
	while(i>1){
		if(array[i]<array[i/2]){
			array[i]=array[i/2];
			array[i/2]=x;
			i/=2;
		}
		else break;
	}
}

template <class T>
T priorityQueue<T>::deQueue(){
	T value=array[1];
	array[1]=array[current--];
	percolateDown(1);
	return value;
}

const int INFINITY=999999;
struct node{
	int end,weight;
	node *next;
	node(int e, int w, node *p=NULL):end(e),weight(w),next(p){}
	node():end(0),weight(0),next(NULL){}
};

struct ver{
	int num, distance;
	ver(): num(0), distance(INFINITY){}
	ver(int num, int d): num(num), distance(d){}
	friend bool operator<(const ver &a, const ver &b){
		return a.distance<b.distance;
	}
	friend bool operator>(const ver &a, const ver &b){
		return a.distance>b.distance;
	}
	friend bool operator<=(const ver &a, const ver &b){
		return a.distance<=b.distance;
	}
	friend bool operator>=(const ver &a, const ver &b){
		return a.distance>=b.distance;
	}
};


bool known[10001] = {0};
int prev[10001] = {0}, dist[10001], vnum[10001] = {0}, nnum[10001] = {0};
node *vers[10001];

void path(int v){
	if (v == 0) return;
	path(prev[v]);
	cout << v << ' ';
}

int main(){
	int n, m, start, end, a, b, p;
	priorityQueue<ver> q;
	cin >> n >> m >> start >> end;
	for (int i = 0; i <= n; ++i) {
		vers[i] = NULL;
		dist[i] = INFINITY;
	}
	for (int i = 0; i < m; ++i){
		cin >> a >> b >> p;
		vers[a] = new node(b, p, vers[a]);
	}

	dist[start] = 0;
	q.enQueue(ver(start,0));
	while(!q.isEmpty()){
		ver tmp=q.deQueue();
		if(known[tmp.num]) continue;
		known[tmp.num]=1;
		if (tmp.num == end) break;
		node *p = vers[tmp.num];
		while(p){
			if(known[p->end] == 0 && (dist[tmp.num] + p->weight < dist[p->end] || dist[p->end] == dist[tmp.num] + p->weight && nnum[p->end] > nnum[tmp.num] + 1)){
				dist[p->end] = dist[tmp.num] + p->weight;
				prev[p->end] = tmp.num;
				nnum[p->end] = nnum[tmp.num] + 1;
				q.enQueue(ver(p->end, dist[p->end]));
			}
			p = p->next;
		}
	}
	cout <<end;
	cout << dist[end] << endl;
	path(end);
	return 0;
}
