// pat advance 1008
// 改进版本
// 使用两个变量取代数组，减少空间复杂度


#include <iostream>

using namespace std;

int main(){
	int n;
	int begin=0,end;
	cin >> n;

	int num = 0;
	for(int i=0;i<n;i++){
		cin >> end;

		int diff = end - begin;
		num += diff>0 ? diff*6+5 : diff*(-4)+5;

		begin = end;

	}

	cout << num << endl;

	return 0;
}