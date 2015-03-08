// 使用并查集求解
// 注意点：
// 1.多次check，每次都需要清空之前的并查集，重新生成。
// 2.细节，注意程序的下标。
// 3.关于count-2：在根节点中，有一个是遭到攻击的，不计算，故需要-1；
//   然后n个等价集合只需要n-1个等价条件将他们变成一个，故又要-1；

#include <iostream>

using namespace std;

#define MAX_CITY 1001
#define MAX_ROAD 500500
	
int root[MAX_CITY];

int findRoot(int x){
	if(root[x] == 0) 
		return x;
	else
		return findRoot(root[x]);
}

void setUnion(int x,int y){
	int i = findRoot(x);
	int j = findRoot(y);
	if(i != j)
		root[j] = i;
}

int main(){
	int N,M,K;
	int highway[MAX_ROAD][2];

	cin >> N >> M >> K;
	
	for(int i=0;i<M;i++)
		cin >> highway[i][0] >> highway[i][1];
	for(int i=0;i<K;i++){
		int check;
		int count = 0;
		cin >> check;
		//clear root[] each time
		for(int j=1;j<=N;j++)
			//attention the index
			root[j] = 0;
		for(int j=0;j<M;j++){
			if(highway[j][0] != check && highway[j][1] != check)
				setUnion(highway[j][0],highway[j][1]);
		}
		for(int j=1;j<=N;j++){
			if(root[j] == 0)
				count++;
		}

		//cout-2:one for check,one for logic(n parts just need n-1 lines)
		cout << count-2 << endl;
	}
}