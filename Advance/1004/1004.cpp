// 使用树的levelTravel
// 开一个数组存储各点的高度，统计各高度上的叶子节点即可

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX 105

//从1开始计数	
vector<int> nodes[MAX];
int depth[MAX];
int cnt[MAX];

//返回最大层数
int levelTravel(){
	queue<int> Q;
	int maxDepth = 0;
	depth[1] = 0;
	Q.push(1);
	while(!Q.empty()){
		int parent = Q.front();
		Q.pop();
		if(nodes[parent].size() == 0)
			cnt[depth[parent]]++;
		for(size_t i=0;i<nodes[parent].size();i++){
			Q.push(nodes[parent][i]);
			depth[nodes[parent][i]] = depth[parent] + 1;
			if(depth[nodes[parent][i]]>maxDepth)
				maxDepth = depth[nodes[parent][i]];
		}
	}

	return maxDepth;

}

int main(){
	int N,M;
	scanf("%d %d",&N,&M);

	for(int i=0;i<M;i++){
		int parent,num;
		scanf("%d %d",&parent,&num);
		for(int j=0;j<num;j++){
			int children;
			scanf("%d",&children);
			nodes[parent].push_back(children);
		}
	}

	for(int i=0;i<N;i++)
		cnt[i] = 0;

	int max = levelTravel();

	printf("%d",cnt[0]);
	for(int i=1;i<=max;i++)
		printf(" %d",cnt[i]);
	printf("\n");

	return 0;
}