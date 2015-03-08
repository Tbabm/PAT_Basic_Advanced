// BFS实现
// 使用STL的queue，最后一个点运行超时

#include <iostream>
#include <queue>

using namespace std;

#define MAX 1005

int map[MAX][MAX];
int visit[MAX];

void bfs(int city,int N){
	queue<int> Q;

	Q.push(city);
	while(!Q.empty()){
		int curCity = Q.front(); 
		Q.pop();
		visit[curCity] = 1;
		for(int i=1;i<=N;i++){
			if(!visit[i] && map[curCity][i])
				Q.push(i);
		}
	}
}

int main(){
	int N,M,K;
	cin >> N >> M >> K;

	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			map[i][j] = 0;

	for(int i=0;i<M;i++){
		int s,e;
		cin >> s >> e;
		map[s][e] = map[e][s] = 1;
	}

	while(K--){
		int check;
		int count = 0;
		cin >> check;

		for(int i=1;i<=N;i++)
			visit[i] = 0;
		visit[check] = 1;
		for(int i=1;i<=N;i++){
			if(!visit[i]){
				bfs(i,N);
				count++;
			}
		}
		cout << count-1 << endl;
	}

	return 0;
}