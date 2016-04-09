// 半满是perferct
// 满了或者空了，会送自行车过去，路上的所有的站点都会被变成perfect
// 最短路径，优先选择需要的车辆数最少的
// 容量：偶数，100封顶，站点数：500封顶，问题站点的index，路数：
// 从1开始编号，PBMC是节点0

// <=n写成了<n
// j++写成了i++
// sent如果是负数也要变成0


#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stack>

#define MAX_STATION 505
#define INF 0x7FFFFFFF

using namespace std;

struct station
{
	int dis;
	int pre;
	int bikes;
	int sent;	// 带权重的最短路径问题
	bool known;
} sta[MAX_STATION];

int map[MAX_STATION][MAX_STATION];
stack<int> ans;

int main()
{
	int c, n, pro, m;

	// 从1计数，多了个0
	scanf("%d%d%d%d",&c,&n,&pro,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&sta[i].bikes);

	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			map[i][j] = -1;

	for(int i=0;i<m;i++){
		int st,en,cost;
		scanf("%d%d%d",&st,&en,&cost);
		map[st][en] = cost;
		map[en][st] = cost;
	}

	sta[0].dis = 0;
	sta[0].pre = -1;
	sta[0].known = 1;
	sta[0].sent = 0;
	for(int i=1;i<=n;i++){
		if(map[0][i] != -1){//相连接的
			sta[i].dis = map[0][i];
			sta[i].pre = 0;
			sta[i].sent = c/2 -sta[i].bikes;
		}
		else{
 			sta[i].dis = INF;
 			sta[i].pre = -1;
 			sta[i].sent = 0;
		}
		sta[i].known = 0;
	}

	for(int i=0;i<=n;i++) //最多判断n次
	{	

		// 逻辑不严谨：当我们找到除root外的第一个点的时候，他的sent没有被初始化！
		int min= INF;
		int index = -1;
		for(int j=0;j<=n;j++)
		{
			// 找出还不知道的里面最小的
			if(!sta[j].known && sta[j].dis < min)
			{
				min = sta[j].dis;
				index = j;
			}
		}

		sta[index].known = 1;

		if(index == pro)
			break;

		// 更新与其相连的节点的状态
		for(int j=0;j<=n;j++)
		{
			if(map[index][j] != -1)
			{
				if(sta[index].dis + map[index][j] < sta[j].dis)
				{
					sta[j].dis = sta[index].dis + map[index][j];
					sta[j].pre = index;
					sta[j].sent = sta[index].sent + c/2 - sta[j].bikes;

				}
				else if((sta[index].dis + map[index][j] == sta[j].dis) && (sta[index].sent + c/2 - sta[j].bikes < sta[j].sent))
				{	
					sta[j].pre = index;
					sta[j].sent = sta[index].sent + c/2 - sta[j].bikes;
				}
			}
		}
	}

	// 注意负数的时候要变成0
	printf("%d ",sta[pro].sent>=0?sta[pro].sent:0);
	int temp = pro;

	while(temp != -1)
	{
		ans.push(temp);
		temp = sta[temp].pre;
	}

	while(ans.size() != 1)
	{
		printf("%d->",ans.top());
		ans.pop();
	}
	printf("%d %d",ans.top(),sta[pro].sent>=0?0:-sta[pro].sent);

	return 0;

}

