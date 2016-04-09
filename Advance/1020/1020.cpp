// distinct positive integers
// 基本思路：
// 根据输入构造出tree，然后leveltravel
// 构造tree使用递归，leveltravel使用queue
// 使用一个vector来装结果，其实使用数组来装也可以，但是vector更方便

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define MAX_NODE 35

struct node
{
	int left;
	int right;
} nodes[MAX_NODE];

queue<int> q;
vector<int> ans;

int buildTree(int post[],int inorder[],int n)
{
	int root;
	int i;

	if(n<=0)
		return -1;
	root = post[n-1];

	// find root's position
	for(i=0;i<n;i++)
		if(inorder[i] == root)
			break;

	nodes[root].left = buildTree(post, inorder, i);
	nodes[root].right = buildTree(post+i, inorder+i+1, n-i-1);

	return root;
}

void travelTree(int root)
{
	q.push(root);
	while(!q.empty())
	{
		int temp;
		temp = q.front();
		q.pop();

		if(nodes[temp].left != -1)
			q.push(nodes[temp].left);
		if(nodes[temp].right != -1)
			q.push(nodes[temp].right);

		ans.push_back(temp);
	}
}

int main()
{
	int n,root;
	int post[MAX_NODE],inorder[MAX_NODE];
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",post+i);
	for(int i=0;i<n;i++)
		scanf("%d",inorder+i);

	root = buildTree(post, inorder, n);
	travelTree(root);

	for(int i=0;i<n-1;i++)
		printf("%d ",ans[i]);

	printf("%d\n",ans[n-1]);

	return 0;
}