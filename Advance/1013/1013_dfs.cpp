// DFS实现
// 改变memset和bool，作用都是微乎其微

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define MAX 1005

vector<int> map[MAX];
bool visit[MAX];

// 递归的dfs
// AC
// time complexity is N^N

/*
void dfs(int city,int N){
	visit[city] = true;
	for(size_t i=0;i<map[city].size();i++){
		if(!visit[map[city][i]])
			dfs(map[city][i],N);
	}
}
*/

// 非递归的dfs
// 最后一个数据过不了，运行超时
void dfs(int city,int N){
	vector<int> stack;

	stack.push_back(city);
	while(!stack.empty()){
		int curCity = stack.back();
		stack.pop_back();
		visit[curCity] = 1;
		for(size_t i=0;i<map[curCity].size();i++)
			if(!visit[map[curCity][i]])
				stack.push_back(map[curCity][i]);
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

		memset(visit,false,(N+1)*sizeof(bool));
		visit[check] = true;
		for(int i=1;i<=N;i++){
			if(!visit[i]){
				dfs(i,N);
				count++;
			}
		}
		printf("%d\n",count-1);
	}

	return 0;
}