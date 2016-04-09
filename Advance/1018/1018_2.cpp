// 问题出在诡异的权重上面：
// 距离最小、携带的自行车最少，带回去的自行车最少

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>

#define MAX_STATION 505
#define INF 0x7FFFFFFF

using namespace std;

struct station
{
	int dis;
	vector<int> pre;
	int bikes;
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
	sta[0].pre.push_back(-1);
	sta[0].known = 1;
	for(int i=1;i<=n;i++){
		if(map[0][i] != -1){//相连接的
			sta[i].dis = map[0][i];
			sta[i].pre.push_back(0);
		}
		else{
 			sta[i].dis = INF;
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
					sta[j].pre.clear();
					sta[j].pre.push_back(index);
				}
				else if(sta[index].dis + map[index][j] == sta[j].dis)
					sta[j].pre.push_back(index);
			}
		}
	}

	// 所有的路径都罗列出来，sent和back算出来
	// 如果只有一条路，选他
	// 如果有多条路，sent<=0的只有一个，选他
	// 如果sent<=0的有多个，选back最小的

	// 方法2：一遍扫描一边记下所有方法的车数和节点数。

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

