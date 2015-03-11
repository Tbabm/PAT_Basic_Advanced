#include <iostream>

using namespace std;

typedef struct BTNode *BTree;	

struct BTNode
{
	int data;
	BTree left;
	BTree right; 
};

bool flag = true;

BTree buildBTree(int* pre,int n){
	if(n <=0 )
		return NULL;

	int i;
	for(i=1;i<n;i++)
		if(*(pre+i) >= *pre)
			break;
	for(int j=i+1;j<n;j++){
		if(*(pre+j) < *pre){
			flag = false;
			return NULL;
		}
	}

	BTree bt = new BTNode;
	bt->data = *pre;
	bt->left = buildBTree(pre+1,i-1);
	if(flag == false)
		return NULL;
	bt->right = buildBTree(pre+i,n-i);
	if(flag == false)
		return NULL;

	return bt;

}

BTree buildMirror(int* pre,int n){
	if(n <=0 )
		return NULL;

	int i;
	for(i=1;i<n;i++)
		if(*(pre+i) < *pre)
			break;
	for(int j=i+1;j<n;j++){
		if(*(pre+j) >= *pre){
			flag = false;
			return NULL;
		}
	}

	BTree bt = new BTNode;
	bt->data = *pre;
	bt->left = buildMirror(pre+1,i-1);
	if(flag == false)
		return NULL;
	bt->right = buildMirror(pre+i,n-i);
	if(flag == false)
		return NULL;

	return bt;

}

void postOrder(BTree root){
	if(root == NULL)
		return;
	postOrder(root->left);
	postOrder(root->right);
	printf("%d ",root->data);
}

void printPost(BTree root){
	//题目已经说明是n>0,但保险起见，还是判断一下
	if(root == NULL)
		return;
	postOrder(root->left);
	postOrder(root->right);
	printf("%d\n",root->data);
}

int main(){
	int num;
	scanf("%d",&num);
	int *pre = new int[num];

	for(int i=0;i<num;i++)
		scanf("%d",pre+i);

	BTree root = new BTNode;
	if(num>1 && *(pre+1) >= *pre)
		root = buildMirror(pre,num);
	else
		root = buildBTree(pre,num);

	if(flag == false)
		printf("NO\n");
	else{
		printf("YES\n");
		printPost(root);
	}

	return 0;
}