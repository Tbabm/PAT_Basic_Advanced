#include <cstdio>
#include <string.h>
#include <algorithm>
using namespace std;

const int N=502,inf=1e9;
int a[N],mp[N][N],dis[N],used[N],visit[N],path[N],tpath[N],plen;
int cmax,n,sp,m,needMin=inf,backMin=inf;

void input(){
	scanf("%d %d %d %d",&cmax,&n,&sp,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		a[i]=a[i]-cmax/2;//多余
	}
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			mp[i][j]=inf;
	for(int i=0,u,v,w;i<m;i++){
		scanf("%d %d %d",&u,&v,&w);
		mp[u][v]=w,mp[v][u]=w;
	}
}
void Dijkstra(){ 	// 用dijkstra算法找出了最短路径
	int k;
	for(int i=1;i<=n;i++)
		dis[i]=mp[0][i];
	for(int i=1;i<=n;i++){
		int tmin=inf;
		for(int j=1;j<=n;j++)
			if(!used[j]&&tmin>dis[j])
				tmin=dis[j],k=j;
		used[k]=1;
		for(int j=1;j<=n;j++)
			if(dis[k]+mp[k][j]<dis[j])
				dis[j]=dis[k]+mp[k][j];
	}
}
void dfs(int x,int dist,int len){
	if(dist>dis[x]) return;//剪枝
	if(x==sp){		// 搜索到了sp，并且为最短路径
		int need=0,get=0;
		for(int i=0;i<len;i++){
			get+=a[tpath[i]];	//tpath中记录的是从起点到终点的深度优先搜索路径
			if(-get>need)
				need=-get;		//要记录的是最大的need，而不是总的need，因为不走回头路
		}
		int back=need+get;		//拿回去的数量

		if(need<needMin||(need==needMin&&back<backMin)){
			needMin=need,backMin=back;
			for(int i=0;i<len;i++)
				path[i]=tpath[i];
			plen=len;
		}
		return;
	}
	//回溯
	for(int i=1;i<=n;i++){
		if(!visit[i]&&mp[x][i]!=inf){ // 对他的每一个儿子
			visit[i]=1;		//标记其已经被回溯
			tpath[len]=i;	//记录搜索路径
			dfs(i,dist+mp[x][i],len+1); //继续深度优先搜索
			visit[i]=0;		//搜索完毕
		}
	}
}
void print(){
	printf("%d %d",needMin,0);
	for(int i=0;i<plen;i++)
		printf("->%d",path[i]);
	printf(" %d\n",backMin);
}
int main(){
	input();
	Dijkstra();
	dfs(0,0,0);
	print();
	return 0;
}