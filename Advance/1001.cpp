// pat 1001
// 模拟即可

#include <iostream>

using namespace std;

#define MAX_NUM 9

int main(){
	int a,b,result;

	cin >> a;
	cin >> b;
	result = a+b;

	char num[MAX_NUM];
	bool negative = false;

	if(result < 0){
		negative = true;
		result = -result;
	}
	else if(result == 0)
		cout << result;

	int count = 0;
	int i = MAX_NUM-1;
	while(result){
		num[i--] = result%10 + '0';		
		result /= 10;
		count++;
		if(count%3 == 0 && result)
			num[i--] = ',';
	}

	if(negative)
		cout << '-';

	for(i=i+1;i<MAX_NUM;i++)
		cout << num[i];

	cout << endl;

	return 0;
}