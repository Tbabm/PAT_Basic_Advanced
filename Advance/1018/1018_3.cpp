// 最短路径 + 回溯剪枝
// 由于need和back在中途是无法确定的，所以无法作为剪枝的条件
// 需要使用最短路径作为剪枝的条件

// need和back那个部分需要动动脑子
// 尽量将输入的东西都放到全局变量里面


#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

#define MAX_STATION 505
#define INF 0x7FFFFFFF

int cap[MAX_STATION],map[MAX_STATION][MAX_STATION];
int known[MAX_STATION] = {0};
int s_dist,pdepth,minPath[MAX_STATION],tPath[MAX_STATION];
int minNeed = INF,minBack=INF;
int n;
int visit[MAX_STATION]= {0};

void dijstra(int start,int end,int n){
	int dist[MAX_STATION];

	for(int i=0;i<=n;i++){
		dist[i] = INF;
	}

	dist[start] = 0;

	for(int i=0;i<=n;i++){	//最多需要循环n次
		int minDist = INF;
		int pos = 0;
		//选出最小的
		for(int j=0;j<=n;j++){
			if(!known[j] && dist[j]<minDist){
				minDist = dist[j];
				pos = j;
			}
		}

		known[pos] = 1;
		if(pos == end)
			break;

		//更新距离
		for(int j=0;j<=n;j++){
			if(map[pos][j] != INF && dist[pos]+map[pos][j] < dist[j])
				dist[j] = dist[pos]+map[pos][j];
		}
	}

	s_dist = dist[end];
}

void dfs(int start, int end, int dist, int depth)		//回溯剪枝
{
	if(dist > s_dist)	//剪枝
		return;

	if(start == end){	//找到了
		int need=0,get=0;
		int back;
		for(int i=0;i<depth;i++){
			get += cap[tPath[i]];
			if(-get > need)
				need = -get;
		}
		back = get + need;

		if(need < minNeed || (need == minNeed && back < minBack)){
			minNeed = need;
			minBack = back;
			pdepth = depth;	
			for(int i=0;i<depth;i++)
				minPath[i] = tPath[i];	//将最短路径更新下来
		}

		return;
	}

	for(int i=0;i<=n;i++){
		if(!visit[i] && map[start][i] != INF){	// 找到儿子
			visit[i] = 1;
			tPath[depth] = i;
			dfs(i,end,dist+map[start][i],depth+1);
			visit[i] = 0;	// 非常重要，为了之后的儿子还能继续使用
		}
	}
}

int main()
{
	int cmax,sp,m;

	scanf("%d%d%d%d",&cmax,&n,&sp,&m);
	for(int i=1;i<=n;i++){
		int tempCap;
		scanf("%d",&tempCap);
		cap[i] = tempCap - cmax/2;
	}

	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			map[i][j] = INF;
	
	for(int i=0;i<m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		map[x][y] = map[y][x] = z; 
	}

	dijstra(0,sp,n);
	visit[0] = 1;
	dfs(0,sp,0,0);

	printf("%d %d",minNeed,0);
	for(int i=0;i<pdepth;i++){
		printf("->%d",minPath[i]);
	}
	printf(" %d\n",minBack);

}