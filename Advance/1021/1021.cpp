// 基本思路：
// 1. 并查集判断是否是树
// 2. 深度优先搜索，拿到first&second,然后进行条件判断，得出答案。

// 一些注意点：
// 1. 如果是图，使用二维数组
// 2. 如果是树，最好使用vector数组
// 3. 可以使用set，避免最后的排序和重复判断

// 9分，还有很多错误
// 思路有误：最长路径有时候可以包括1，而两条最长的路径应该也可能在叶子节点共用同一个父节点
// 尝试下面的例子：
// 6
// 1 2
// 2 3
// 3 4
// 3 5
// 2 6

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_NUM	10005

using namespace std;

int n, tree=true;
int pre[MAX_NUM],visit[MAX_NUM]={0};
int depth1=0,depth2=0;
vector<int> edge[MAX_NUM];
vector<int> first,second;

int Find(int node)
{
	if(pre[node] == node)
		return node;
	else
		return Find(pre[node]);
}

void Union(int x,int y)
{
	int rootx = Find(x);
	int rooty = Find(y);

	if(rootx != rooty)
		pre[y] = x;
	else	//两个节点有相同的root，却还要join，说明形成了回路，不是树
		tree = false;
}

void dfs(int root,int depth)
{
	visit[root] = 1;

	// 注意，可能出现只有一个vector有值的情况
	// 不能使用size==0来判断是否是叶子节点，因为它必然和父节点连在一起的，所以还有size==1的情况
	if(edge[root].size() == 0 || edge[root].size() == 1){ // 叶子节点
		if(depth > depth1){
			depth2 = depth1;
			depth1 = depth;
			second = first;
			first.clear();
			first.push_back(root);
		}
		else if(depth == depth1){
			first.push_back(root);
		}
		else if(depth > depth2){
			depth2 = depth;
			second.clear();
			second.push_back(root);
		}
		else if(depth == depth2){
			second.push_back(root);
		}
	}

	for(int i=0;i<edge[root].size();i++){
		// 可能是他的父节点，所以需要加上==0
		if(visit[edge[root][i]] == 0)
			dfs(edge[root][i],depth+1);
	}

}

int main()
{
	int com=0;

	scanf("%d",&n);

	// 初始化并查集
	for(int i=1;i<=n;i++)
		pre[i] = i;
	
	for(int i=1;i<n;i++){
		int temp1,temp2;
		scanf("%d%d",&temp1,&temp2);
		edge[temp1].push_back(temp2);
		edge[temp2].push_back(temp1);
		Union(temp1,temp2);
	}

	// 判断有几个component
	for(int i=1;i<=n;i++)
		if(pre[i] == i)
			com++;

	if(com>1 || !tree){
		printf("Error: %d components",com);
		return 0;
	}
	
	dfs(1,0);

	if(first.size()>1){
		sort(first.begin(),first.end());
		for(int i=0;i<first.size();i++)
			printf("%d\n",first[i]);
	}
	else if(second.size() == 0)
		printf("%d\n",first[0]);
	else{
		second.push_back(first[0]);
		sort(second.begin(),second.end());
		for(int i=0;i<second.size();i++)
			printf("%d\n",second[i]);
	}

	return 0;

}
