//pat advance 1008
//猜测版本：
//找到驼峰
//驼峰之前的请求升序进行，驼峰之后的请求降序进行
//在考虑停留时间时，需要对前后两个部分分别去重

#include <iostream>

using namespace std;

int main(){
	int n;
	int floor[100];
	cin >> n;

	int max = 0,index = 0;
	for(int i=0;i<n;i++){
		cin >> floor[i];
		if(floor[i]>max){
			max = floor[i];
			index = i;
		}
	}

	for(int i=index;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			if(floor[i]<floor[j]){
				int temp;
				temp = floor[i];
				floor[i] = floor[j];
				floor[j] = temp;
			}
			
		}
	}

	for(int i=0;i<index-1;i++){
		for(int j=i+1;j<index;j++){
			if(floor[i]>floor[j]){
				int temp;
				temp = floor[i];
				floor[i] = floor[j];
				floor[j] = temp;
			}
		}
	}

	int num = n;
	for(int i=1;i<n;i++){
		if(floor[i] == floor[i-1])
			num --;
	}

	int amount = 0;
	// cout << max << " " << floor[n-1] << " " << num << endl;
	amount = max*6 + (max - floor[n-1])*4 + num*5;

	// 	if(i==0)
	// 		num += floor[i]*6+5;
	// 	else if(floor[i] != floor[i-1]){
	// 		int diff;
	// 		diff = floor[i]-floor[i-1];
	// 		num += diff>0 ? diff*6+5 : diff*(-4)+5;
	// 	}

	cout <<amount << endl;

	return 0;
}