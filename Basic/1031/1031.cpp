#include <iostream>
#include <cctype>
#include <string>

using namespace std;

int main(){
	int n;
	int weight[17]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
	char M[11]={'1','0','X','9','8','7','6','5','4','3','2'};
	string num;

	cin >> n;
	int count =0;
	for(int i=0;i<n;i++){
		cin >> num;
		int flag = 0;
		int sum =0;
		for(int j=0;j<17;j++){
			if(isdigit(num[j]))
				sum += ((num[j]-'0')*weight[j]);
			else{
				flag = 1;
				break;
			}
		}
		if(num[17] != M[sum%11]){
			flag = 1;
		}
		if(flag){
			cout << num << endl;
			count ++;
		}
	}
	if(count == 0)
		cout << "All passed"<<endl;

	return 0;
}