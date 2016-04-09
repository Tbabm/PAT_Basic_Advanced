// 超时……醉了

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	clock_t st = clock();

	long long num;
	scanf("%lld",&num);

	int cur_len=0,max_len=0;
	long long cur_factors;
	long long max_start,max_end;
	long long i=2,start,end; //可能有问题，万一不从2开始呢？比如质数

	while(num%i != 0)	// 搞定了质数的情况
		i++;

	// 如果是1个数，那么会较小的那个，肯定是小于sqrt(n)
	// 如果是两个数，那么大于sqrt(n)的数一定不可能是答案

	max_start=max_end=i;
	start=end=cur_factors=i;
	cur_len=1,max_len=1;
	i++;

	for(;i*i<num;i++){
		cur_factors = i*cur_factors;
		if(num%cur_factors == 0){
			cur_len++;
			end = i;
			if(cur_len > max_len){
				max_len = cur_len;
				max_start = start;
				max_end = end;
			}
		}
		else{
			cur_len++;
			while(start<=i && num%cur_factors!=0){
				cur_factors = cur_factors/start;
				start++;
				cur_len--;
			}
		}
	}

	printf("%d\n",max_len);
	printf("%lld",max_start);
	for(long long j=max_start+1;j<=max_end;j++){
		printf("*%lld",j);
	}

	printf("\n");

	clock_t en = clock();
	cout << (double)(en-st)/CLOCKS_PER_SEC <<endl;
}

// csdn上面有一个限定头，变化尾的 n^2算法
// http://blog.csdn.net/cstopcoder/article/details/45849245