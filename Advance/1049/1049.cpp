// 此题应该不用用到long long，count最多不会超过10^9，2^30使得num的数量最多也不会超过int的正整数范围
// 因此，没有必要使用long long
// 此题的主要难度在于while中的那个if else，需要好好理解。

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int main()
{
	int n,temp,count=1;
	long long num =0;
	scanf("%d",&n);

	temp = n;
	while(temp != 0)
	{
		if(temp%10 > 1)
			num += (1 + temp/10) * count;
		else if(temp%10 == 1)
			num += n%count+1 + temp/10*count;
		else
			num += temp/10*count;

		count *= 10;
		temp /= 10;
	}

	printf("%lld\n",num);
}