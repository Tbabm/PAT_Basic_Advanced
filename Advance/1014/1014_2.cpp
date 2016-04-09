#include <iostream>
#include <queue>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define MAX_WINDOWS 22
#define MAX_CAPACITY 12
#define MAX_CUSTOMER 1002
#define INF 0x7fffffff
struct customer
{
	int cost;
	int start;
	int end;
} cus[MAX_CUSTOMER];

struct window
{
	int end;
	queue<struct customer> que;
} win[MAX_WINDOWS];


int n,m,k,q;
int query[MAX_CUSTOMER];

int main()
{
	scanf("%d %d %d %d",&n,&m,&k,&q);
	for(int i=0;i<k;i++)
		scanf("%d",&cus[i].cost);
	for(int i=0;i<q;i++)
		scanf("%d",query+i);
	
	for(int i=0;i<n;i++)
		win[i].end = 0;

	int i,j=0;

	for(i=0;i<k && i<n*m;i++,j=(j+1)%n)
	{
		cus[i].start = win[j].end;
		cus[i].end = cus[i].start + cus[i].cost;
		win[j].end += cus[i].cost;
		win[j].que.push(cus[i]);	//加入队列
	}

	for(;i<k;i++)
	{
		//找到各排front中结束时间最早的
		int minTime = INF;
		int pos = 0;
		for(int x=0;x<n;x++)
		{
			if(win[x].que.front().end < minTime){
				minTime = win[x].que.front().end;
				pos = x;
			}
		}

		// 插入这个队列
		win[pos].que.pop(); // pop出旧的
		cus[i].start = win[pos].end;
		cus[i].end = cus[i].start + cus[i].cost;
		win[pos].end += cus[i].cost;
		win[pos].que.push(cus[i]);	//加入队列

	}

	// for(int x=0;x<k;x++)
	// 	cout << cus[x].end << endl;

	// 猜测结束时间一定在本日	
	for(int x=0;x<q;x++)
	{
		if(cus[query[x]-1].start >= 540)
			printf("Sorry\n");
		else	
			printf("%02d:%02d\n",cus[query[x]-1].end/60+8,cus[query[x]-1].end%60);
	}

	return 0;
}