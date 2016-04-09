// 每个队列的大小都是正数
// 考merge算法
// merge算法在某一列算完之后，会直接算另外一列！这点要注意。

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

int main()
{
	int size[2];
	queue<long> q[2];

	for(int i=0;i<2;i++){
		scanf("%d",size+i);
		for(int j=0;j<size[i];j++){
			long temp;
			scanf("%ld",&temp);
			q[i].push(temp);
		}
	}

	int count = 0;
	int mid =(size[0]+size[1]+1)/2;
	long median;

	while(count < mid){
		// 切记，判断为空的情况！
		if(q[0].size() == 0){
			median = q[1].front();
			q[1].pop();
		}
		else if(q[1].size() == 0){
			median = q[0].front();
			q[0].pop();
		}
		else if(q[0].front() <= q[1].front()){
			median = q[0].front();
			q[0].pop();
		}
		else{
			median = q[1].front();
			q[1].pop();
		}

		count++;		
	}

	printf("%ld",median);
}