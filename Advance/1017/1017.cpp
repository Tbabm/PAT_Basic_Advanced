// 个人的最长服务时间不超过1小时
// 轮到他，并且有空窗
// 到达时间，开始服务的时间，结束服务的时间

// C中struct的tag是二等公民，而C++中被当成类型名使用

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <algorithm>

using namespace std;

#define MAX_CUS_NUM 10005
#define MAX_WIN_NUM 105

#define INF 0x7FFFFFFF

// 排序
// 开头结尾有个时间控制
// 用front保证是第一个，搞出一个空窗(选最小)，判断首尾

struct customer
{
	int arr;
	int wait;
	int pro;
	int st;
} cus[MAX_CUS_NUM];

struct window
{
	int end;
	struct customer cu;
} win[MAX_WIN_NUM];

int n,k;

bool cmp(struct customer a, struct customer b)
{
	return a.arr < b.arr;
}

int main()
{
	scanf("%d %d",&n,&k);
	for(int i=0;i<n;i++)
	{
		int hour,min,sec,proMin;
		scanf("%d:%d:%d %d",&hour,&min,&sec,&proMin);
		cus[i].pro = proMin*60;
		cus[i].arr = hour*3600 + min*60 + sec;
	}

	sort(cus,cus+n,cmp);

	for(int i=0;i<k;i++)
		win[i].end = 8*3600;

	int count = n;
	int totalWait = 0;
	for(int i=0;i<n;i++)
	{
		
		// 17:00之后到的不予处理
		if(cus[i].arr > 17*3600)
		{
			count--;
			cus[i].wait = 0;
		}
		else
		{
			// 选出最小的窗口，进去，更新自己的各项数据
			int minTime = INF;
			int pos = 0;
			for(int j=0;j<k;j++)
			{
				if(win[j].end < minTime)
				{
					minTime = win[j].end;
					pos = j;
				}
			}

			// 出现空窗期
			if(cus[i].arr > win[pos].end)
				win[pos].end = cus[i].arr;

			cus[i].st = win[pos].end;
			cus[i].wait = cus[i].st - cus[i].arr;
			totalWait += cus[i].wait;
			win[pos].end += cus[i].pro;
		}
	}

	// for(int i=0;i<n;i++)
	// {
	// 	cout << i << ":" << endl;
	// 	cout << cus[i].arr << endl;
	// 	cout << cus[i].pro << endl;
	// 	cout << cus[i].st << endl;
	// 	cout << cus[i].wait << endl;
	// 	cout << endl;
	// }

	// cout << totalWait <<endl;

	double ave;
	if(count)
		ave = (double)totalWait/count/60;
	else
		ave = 0;


	printf("%.1f\n",ave);
}