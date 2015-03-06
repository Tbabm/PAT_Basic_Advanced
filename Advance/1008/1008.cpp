// pat advance 1008
// 无脑版本，一个一个算
// 坑点：相邻请求如果楼层相同，停留时间也需要增加


#include <iostream>

using namespace std;

int main(){
	int n;
	int floor[100];
	cin >> n;

	int num = 0;
	for(int i=0;i<n;i++){
		cin >> floor[i];

		if(i==0)
			num += floor[i]*6+5;
		else{
			int diff;
			diff = floor[i]-floor[i-1];
			num += diff>0 ? diff*6+5 : diff*(-4)+5;
		}
	}

	cout << num << endl;

	return 0;
}