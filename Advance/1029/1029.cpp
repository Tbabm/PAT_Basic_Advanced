// 每个队列的大小都是正数

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

int main()
{
	int size[2];
	queue<long long> q[2];

	for(int i=0;i<2;i++){
		scanf("%d",size+i);
		for(int j=0;j<size[i];j++){
			long long temp;
			scanf("%lld",&temp);
			q[i].push(temp);
		}
	}

	int count = 0;
	int mid =(size[0]+size[1]+1)/2;
	long long median;

	while(count < mid){
		if(q[0].front() <= q[1].front()){
			median = q[0].front();
			q[0].pop();
		}
		else{
			median = q[1].front();
			q[1].pop();
		}

		count++;		
	}

	printf("%lld",median);
}