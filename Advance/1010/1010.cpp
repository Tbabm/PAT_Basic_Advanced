// 错误:
// 1.复制粘贴时的下标，计算时的+=
// 2.并没有说进制不能超过36，事实上，题目的基数可以非常大
// 3.测试的数据比较大，虽然不用使用大数，但是目标数和基数都需要使用long long 
// 4.忘了删掉debug用的cout……
// 改正上述三点之后仍然有一个超时，搜索网上发现，寻找基数的时候需要使用二分法……

#include <iostream>
#include <vector>

using namespace std;

int main(){
	vector<char> num[2];

	char ch;
	while((ch=getchar()) != ' ')
		num[0].push_back(ch);

	while((ch=getchar()) != ' ')
		num[1].push_back(ch);

	int tag,radix;
	scanf("%d %d",&tag,&radix);

	long long value = 0;
	for(long long i=0;i<num[tag-1].size();i++){
		if(num[tag-1][i] > '9')
			value = value*radix + (num[tag-1][i]-'a'+10);
		else
			value = value*radix + (num[tag-1][i]-'0');
	}

	char maxCh='0';
	for(size_t i=0;i<num[2-tag].size();i++)
		if(num[2-tag][i] > maxCh)
			maxCh = num[2-tag][i];

	int maxInt = maxCh>'9' ? maxCh-'a'+10 : maxCh-'0';

	bool flag = true;
	int radix2;
	//题意应该允许36进制以上进制的存在
	for(radix2 = maxInt+1;;radix2++){
		long long value2=0;
		for(size_t i=0;i<num[2-tag].size();i++){
			if(num[2-tag][i] > '9')
				value2 = value2*radix2 + (num[2-tag][i]-'a'+10);
			else{
				value2 = value2*radix2 + (num[2-tag][i]-'0');
			}
		}

		if(value2 == value)
			break;
		if(value2 > value){
			flag = false;
			break;
		}
	}

	if(flag)
		printf("%d\n",radix2);
	else
		printf("Impossible\n");

	return 0;
	
}