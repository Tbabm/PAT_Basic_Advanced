// DFS实现

#include <iostream>
// #include <stack>

using namespace std;

#define MAX 1005

int map[MAX][MAX];
int visit[MAX];

// 递归的dfs
// AC
// time complexity is N^N
/*
void dfs(int city,int N){
	visit[city] = 1;
	for(int i=1;i<=N;i++){
		if(!visit[i] && map[city][i])
			dfs(i,N);
	}
}
*/

// 非递归的dfs
// time complexity is N*N
// 使用STL：最后一个case超时
// 使用自己写的stack：段错误，修改MAX无用
class MyStack{
private:
	int member[MAX];
	int location;

public:
	MyStack(){
		location = 0;
	}

	void push(int city){
		member[location++] = city;
	}

	int top(){
		return member[location-1];
	}

	void pop(){
		location--;
	}

	bool empty(){
		return !location;
	}
};

void dfs(int city,int N){
	//stack<int> S;
	MyStack S;

	S.push(city);
	while(!S.empty()){
		int curCity = S.top();
		S.pop();
		visit[curCity] = 1;
		for(int i=1;i<=N;i++)
			if(!visit[i] && map[curCity][i])
				S.push(i);

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
				dfs(i,N);
				count++;
			}
		}
		cout << count-1 << endl;
	}

	return 0;
}