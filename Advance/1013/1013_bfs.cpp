// BFS实现
// 使用STL的queue，最后一个点运行超时

#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

#define MAX 1005

vector<int>	map[MAX];
int visit[MAX];

void bfs(int city,int N){
	queue<int> Q;

	Q.push(city);
	// pay attention to index
	while(!Q.empty()){
		int curCity = Q.front(); 
		Q.pop();
		visit[curCity] = 1;
		for(vector<int>::size_type i=0;i<map[curCity].size();i++){
			if(!visit[map[curCity][i]])
				Q.push(map[curCity][i]);
		}
	}
}

int main(){
	int N,M,K;
	scanf("%d %d %d",&N,&M,&K);

	for(int i=0;i<M;i++){
		int s,e;
		scanf("%d %d",&s,&e);
		map[s].push_back(e);
		map[e].push_back(s);
	}

	while(K--){
		int check;
		int count = 0;
		scanf("%d",&check);

		memset(visit,0,(N+1)*sizeof(int));
		visit[check] = 1;
		for(int i=1;i<=N;i++){
			if(!visit[i]){
				bfs(i,N);
				count++;
			}
		}
		printf("%d\n",count-1);
	}

	return 0;
}