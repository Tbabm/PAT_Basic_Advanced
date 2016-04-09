// 切记实现树节点的方法！！！！ l
// 结构数组，下标表示自己是哪个节点，left表示左儿子的下标，right表示右儿子的下标

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <stack>

#define MAX 35

using namespace std;

int root;
stack<int> tree;

struct node {
	int left;
	int right;
} nodes[MAX];

int buildTree(int pre[],int in[],int nu){
	int i;

	// 细节决定成败呀！
	// 当右子树为空的时候，nu完全可能等于0，此时pre[]会是乱码，不能够返回！
	// 右子树也有可能出现小于0的情况，所以一定要考虑周全
	if(nu <= 0)
		return -1;

	for(i=0;i<nu;i++){
		if(pre[0] == in[i])
			break;
	}

	nodes[pre[0]].left = buildTree(pre+1,in,i);
	nodes[pre[0]].right = buildTree(pre+i+1,in+i+1,nu-i-1);

	return pre[0];
}

void postTravel(int s){
	if(s<=0)
		return;

	postTravel(nodes[s].left);
	postTravel(nodes[s].right);
	if(s == root)
		printf("%d\n",s);
	else
		printf("%d ",s);
}


int main()
{
	int n,pre[MAX],in[MAX];
	int ppre=0,pin=0;
	scanf("%d",&n);
	// 2n次
	for(int i=0;i<2*n;i++){
		char op[10];
		int num;

		scanf("%s",op);
		if(op[1] == 'u'){
			scanf("%d",&num);
			tree.push(num);
			pre[ppre++] = num;
		}
		else if(op[1] == 'o'){
			num = tree.top();
			tree.pop();
			in[pin++] = num;
		}
	}

	// 从1开始
	for(int i=1;i<=n;i++){
		nodes[i].left = -1;
		nodes[i].right = -1;
	}

	root = buildTree(pre, in, n);
	postTravel(root);

	return 0;
}