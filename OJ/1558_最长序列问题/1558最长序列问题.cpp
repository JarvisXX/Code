#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define N 1000003

int n,m,a[N],b[N],p[N],newn[N],cnt;

int q[N],key[N],pd[N];

struct data
{
    int pos,x;
}; 
data num[N];

int cmp(data x,data y)
{
  return x.x<y.x;
}

int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i)
    {
        scanf("%d",&num[i].x);
        num[i].pos=i;
    }

    sort(num+1,num+n+1,cmp);

    cnt=0;
    ++cnt; 
    newn[num[1].pos]=cnt;
    for(int i=2;i<=n;++i)
        if(num[i].x!=num[i-1].x)
        {
            ++cnt;
            newn[num[i].pos]=cnt;
        }
    else  
        newn[num[i].pos]=cnt;
    //cout<<cnt<<endl;
    ++m; 
    m=min(cnt,m);
    int head=1; 
    int tail=1; 
    int maxn=0;
    ++pd[tail]; 
    q[tail]=newn[tail]; 
    ++key[newn[1]]; 
    maxn=1;
    while(head<=tail)
    {
   	    ++tail;
        pd[tail]=pd[tail-1];
        if(pd[tail]>=m) 
            break;
        if(!key[newn[tail]])   
            pd[tail]++;
        key[newn[tail]]++;
        q[tail]=newn[tail];
        maxn=max(maxn,key[newn[tail]]);
    }
    while (head<=tail&&tail<=n)
    {
        while (key[newn[tail]]&&head<=tail) 
        {
   	        q[tail]=newn[tail];
   	        maxn=max(maxn,++key[newn[tail]]);
   	        tail++;
        }
        while(!key[newn[tail]]&&head<tail)
        {
            key[newn[head]]--; 
            head++;
            if(!key[newn[head-1]]) 
	          {
	              key[newn[tail]]++; 
                q[tail]=newn[tail];
	              maxn=max(maxn,key[newn[tail]]); 
                tail++;
	              break;
	          }
        }
    }
    printf("%d",maxn);
}
