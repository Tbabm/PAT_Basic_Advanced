// 3的改进版本

#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

#define MAX_STATION 505
#define INF	0x7FFFFFFF

int cmax,n,sp,m;
int cap[MAX_STATION],map[MAX_STATION][MAX_STATION];
int minDist,minNeed=INF,minBack=INF;
int tpath[MAX_STATION],minPath[MAX_STATION],minDepth;
int visit[MAX_STATION];

void dijstra()
{
	int dist[MAX_STATION];
	int known[MAX_STATION] = {0};

	for(int i=0;i<=n;i++)
		dist[i] = INF;

	dist[0] = 0;

	for(int i=0;i<=n;i++){	//最多循环n+1次
		//寻找最小的
		int tempDist=INF,pos=0;
		for(int j=0;j<=n;j++){
			if(!known[j] && dist[j]<tempDist){
				tempDist = dist[j];
				pos = j;
			}
		}

		known[pos] = 1;
		if(pos == sp)
			break;

		// 更新距离
		for(int j=0;j<=n;j++){
			if(map[pos][j] != INF && map[pos][j]+dist[pos] < dist[j])
				dist[j] = map[pos][j]+dist[pos];
		}
	}

	minDist = dist[sp];
}

// root:当前子树的根节点
// dist:从根节点到i的距离
// depth:i的深度
// 因为0是根节点，所以我们在循环的时候根本不用考虑0

void dfs(int root,int dist,int depth)
{
	// 剪枝
	if(dist>minDist)
		return;
	// 找到了其中一个解
	if(root == sp){
		int need=0,get=0;
		int back;
		for(int i=0;i<depth;i++){
			get += cap[tpath[i]];
			if(-get > need)
				need = -get;
		}
		back = get + need;

		if(need<minNeed || (need == minNeed && back < minBack)){
			minNeed = need;
			minBack = back;
			minDepth = depth;
			for(int i=0;i<depth;i++)
				minPath[i] = tpath[i];
		}

		return;
	}

	// 否则，继续找
	for(int i=1;i<=n;i++){
		if(!visit[i] && map[root][i]!=INF){	//不在这条路上，并且是我的儿子
			tpath[depth] = i;				// 记录下这条路径！
			visit[i] = 1;
			dfs(i,dist+map[root][i],depth+1);
			visit[i] = 0;
		}
	}
}

int main()
{
	scanf("%d%d%d%d",&cmax,&n,&sp,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",cap+i);
		cap[i] -= cmax/2;
	}

	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			map[i][j] = INF;

	for(int i=0;i<m;i++){
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		map[x][y] = map[y][x] = z;
	}

	dijstra();	//获取最短路径
	dfs(0,0,0);		//用深度优先搜索来遍历每一条路径，得到最小值
				//与for循环找最小值类似

	printf("%d %d",minNeed,0);
	for(int i=0;i<minDepth;i++)
		printf("->%d",minPath[i]);
	printf(" %d\n",minBack);
}