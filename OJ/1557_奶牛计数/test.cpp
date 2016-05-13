#include <iostream>
#include <cstdlib>
using namespace std;

template <class elemType>
class linkStack
{
private:
    struct node
    {
        elemType x_data;
        elemType h_data;
        node *next;
        node (const elemType &x, const elemType &h, node *N=NULL)
        {
            x_data = x;
            h_data = h;
            next = N;
        }
        node():next(NULL) {}
        ~node() {}
    };
    node *top;
public:
    linkStack();
    ~linkStack();
    bool isEmpty() const;
    elemType getTop_h() const;
    elemType getTop_x() const;
    elemType pop();
    void push(const elemType &x, const elemType &h);
};

template <class elemType>
linkStack<elemType>::linkStack()
{
    top = NULL;
}

template <class elemType>
linkStack<elemType>::~linkStack()
{
    node *tmp;
    while (top!=NULL)
    {
        tmp = top;
        top = top->next;
        delete tmp;
    }
}

template <class elemType>
bool linkStack<elemType>::isEmpty() const
{
    return top==NULL;
}

template <class elemType>
elemType linkStack<elemType>::getTop_x() const
{
    if (isEmpty())
    {
        cout << "The stack is empty.";
        exit(0);
    }
    return top->x_data;
}

template <class elemType>
elemType linkStack<elemType>::getTop_h() const
{
    if (isEmpty())
    {
        cout << "The stack is empty.";
        exit(0);
    }
    return top->h_data;
}

template <class elemType>
elemType linkStack<elemType>::pop()
{
    if (isEmpty())
    {
        cout << "The stack is empty.";
        exit(0);
    }
    node *tmp=top;
    elemType x=top->x_data;
    top = top->next;
    delete tmp;
    return x;
}

template <class elemType>
void linkStack<elemType>::push(const elemType &x, const elemType &h)
{
    node *tmp=new node(x, h, top);
    top = tmp;
}

void Qsort(int a[], int b[], int low, int high)
{
    int first = low;
    int last = high;
    int key = a[(low+high)/2];
    int mid;

    while (first<=last)
    {	while (a[first]<key)
            ++first;
        while (a[last]>key)
            --last;
        if (first<=last)
        {
            mid = a[first];
            a[first] = a[last];
            a[last] = mid;
            mid = b[first];
            b[first] = b[last];
            b[last] = mid;
            ++first;
            --last;
        }
    }

    if (first<high)
        Qsort(a, b, first, high);
    if (last>low)
        Qsort(a, b, low, last);
}

int main()
{
    int N, D;
    int *x=new int[50010];
    int *h=new int[50010];
    cin >> N >> D;
    for (int i=0; i<N; ++i)
        cin >> x[i] >> h[i];
    Qsort(x, h, 0, N-1);
    int cnt=0;
    linkStack<int> cattleR;
    linkStack<int> finding;
    for (int i=0; i<N; ++i)
        cattleR.push(x[i], h[i]);
    for (int i=0; i<N; ++i)
    {
        int h_0=cattleR.getTop_h();
        int x_0=cattleR.pop();
        finding.push(x_0, h_0);
        bool flag=0;
        int h_tmp, x_tmp;
        while(!cattleR.isEmpty())
        {
            h_tmp=cattleR.getTop_h();
            x_tmp=cattleR.pop();
            //cout <<"x_0:"<<x_0<<' '<<"h_0:"<<h_0<<' '<<"x_tmp:"<<x_tmp<<' '<<"h_tmp:"<<h_tmp<<endl;
            finding.push(x_tmp, h_tmp);
            if (!flag && h_0>=2*h_tmp && x_0-x_tmp<=D)
            {
                flag = 1;
                h_0 = h_tmp;
                x_0 = x_tmp;
            }
            if (flag && h_tmp>=2*h_0 && x_0-x_tmp<=D)
            {
                ++cnt;
                while(!finding.isEmpty())
                {
                    h_tmp = finding.getTop_h();
                    x_tmp = finding.pop();
                    if (x_tmp!=x_0)
                        cattleR.push(x_tmp, h_tmp);
                }
                flag = 0;
                break;
            }
        }
        while(!finding.isEmpty())
        {
            h_tmp = finding.getTop_h();
            x_tmp = finding.pop();
            if (x_tmp!=x_0)
                cattleR.push(x_tmp, h_tmp);
        }
    }
    cout << cnt;
}
