#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int num,base,tempSize;
	vector<int> v;
	bool flag = true;

	scanf("%d%d",&num,&base);

	if(num == 0){
		printf("Yes\n");
		printf("%d",num);
		return 0;
	}

	while(num != 0){
		v.push_back(num%base);
		num /= base;	
	}

	tempSize = v.size();
	for(int i=0,j=tempSize-1;i<tempSize/2;i++,j--){
		if(v[i] != v[j])
			flag = false;
	}

	if(flag)
		printf("Yes\n");
	else
		printf("No\n");

	printf("%d",v.back());
	v.pop_back();
	while(!v.empty()){
		printf(" %d",v.back());
		v.pop_back();
	}

	return 0;
}
