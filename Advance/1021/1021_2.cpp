// 思路：
// 1. 并查集搞定tree是否合法的判断：因为只有n-1条边，所以如果只有一个component，那就一定是树。
// 2. 两次dfs，第一次找出其中一个depthest root，第二次找出剩下的。具体证明应该可以通过递推的方式得到。
// 3. 任意进行一次dfs，拿到一堆最长路径的叶子节点，这些叶子节点一定是depthest root。
// 4. 在用任意一个叶子节点再进行一次dfs，拿到第二堆最长路径的叶子节点，这些节点就是第二批depthest root.

// 注意：
// 1. 每次dfs之前，都需要重新初始化maxdepth和visit！因为我们的扫描已经变了
// 2. 用set是因为两次扫描得到的点里面有重合，并且后面需要排序
// 3. 更新最大值
// 4. 注意并查集的用法！不是指向父节点，而是指向根节点，更新也是更新根节点！

// 边界情况：
// 1. 只有一个节点

// 6
// 1 2
// 2 3
// 4 5
// 5 6
// 1 6

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>

#define MAX_NUM 10005

using namespace std;

// point要初始化为1，应对只有一个节点的情况
int n,point=1,maxDep;
int pre[MAX_NUM],visit[MAX_NUM]={0};
vector<int> edge[MAX_NUM];
set<int> q,out;

int Find(int x)
{
	if(pre[x] == x)
		return x;
	else
		//可以改进
		// return Find(pre[x]);
		return pre[x] = Find(pre[x]);
}

void Union(int x,int y)
{
	int mx = Find(x);
	int my = Find(y);

	if(mx != my)
		// 错误：这个地方的错误导致最后两个点过不了
		// pre[y] =  x;
		pre[my] = mx;
}

void dfs(int root,int depth)
{
	// 更新depthest one
	if(depth > maxDep){
		maxDep = depth;
		q.clear();
		q.insert(root);
		point = root;
	}
	else if(depth == maxDep){
		q.insert(root);
	}

	visit[root] = 1;
	for(int i=0;i<edge[root].size();i++){
		if(visit[edge[root][i]] == 0)	// 避免扫描其父节点
			dfs(edge[root][i],depth+1);
	}
}

int main()
{
	set<int>::iterator it;

	scanf("%d",&n);

	for(int i=1;i<=n;i++)
		pre[i] = i;

	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		edge[x].push_back(y);
		edge[y].push_back(x);
		Union(x,y);
	}

	int com = 0;
	for(int i=1;i<=n;i++)
		if(pre[i] == i)
			com ++;

	if(com > 1){
		printf("Error: %d components\n",com);
		return 0;
	}

	maxDep = 0;	
	dfs(1,0);

	for(it=q.begin();it!=q.end();it++)
		out.insert(*it);

	q.clear();
	// 因为没有初始化visit，导致第二次的扫描出现所有的节点都被visit的情况。
	memset(visit,0,sizeof(visit));
	dfs(point,0);

	for(it=q.begin();it!=q.end();it++)
		out.insert(*it);

	for(it=out.begin();it!=out.end();it++)
		printf("%d\n",*it);

	return 0;
}

// 需要继续加深理解的东西：
// 1. 并查集的工作原理
// 2. 两次dfs达成目标的证明