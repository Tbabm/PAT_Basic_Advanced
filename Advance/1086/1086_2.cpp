#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <stack>

#define MAX 35

using namespace std;

struct Node
{
    int left;
    int right;
} nodes[MAX];

int root;

int buildTree(int po[],int io[],int nu){
    int i;

    if(nu <= 0) //切记return -1，这里也有初始化的作用
        return -1;

    for(i=0;i<nu;i++)
        if(po[0] == io[i])
            break;

    nodes[po[0]].left = buildTree(po+1,io,i);
    nodes[po[0]].right = buildTree(po+i+1,io+i+1,nu-i-1);
    
    return po[0];
}

void postTravel(int src){
    if(src<=0)
        return;

    postTravel(nodes[src].left);
    postTravel(nodes[src].right);

    if(src == root)
        printf("%d\n",src);
    else
        printf("%d ",src);
}

int main()
{
    int n,pre[MAX],in[MAX];
    int ppre=0,pin=0;
    stack<int> tree;

    scanf("%d",&n);
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

    // 并不需要初始化nodes

    root = buildTree(pre,in,n);
    postTravel(root);

    return 0;
