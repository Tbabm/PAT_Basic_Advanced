// 需要使用long long
// 300ms，应该是n*logn的复杂度
// 全部是正整数

// 测试点5就是卡long long

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int n;
	long long p;
	vector<long long> seq;

	scanf("%d %lld",&n,&p);
	for(int i=0;i<n;i++){
		long long temp;
		scanf("%lld",&temp);
		seq.push_back(temp);
	}

	sort(seq.begin(),seq.end());

	int max_num = 0,this_num = 0;
	int min_pos = 0;
	long long min = seq[min_pos],max;
	for(int i=0;i<n;i++){
		max = seq[i];
		this_num++;
		if(max <= min*p && this_num>max_num){
			max_num = this_num;
		}
		else if(max>min*p){
			while(max>min*p){
				this_num--;
				min_pos++;
				min = seq[min_pos];
			}
			// if(this_num > max_num) //此时不可能比max_num大，最多一样大
			// 	max_num = this_num;
		}
	}

	printf("%d\n",max_num);

	return 0;

}