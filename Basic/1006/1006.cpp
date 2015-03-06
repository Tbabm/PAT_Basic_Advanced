#include <iostream>
#include <cmath>

using namespace std;

int main(){
	int input;

	cin >> input;

	for(int i=2;i>=0;i--){
		int num = input/((int)pow(10.0,i));
		for(int j=0;j<num;j++){
			switch(i){
				case 2:
					cout << "B";
					break;
				case 1:
					cout << "S";
					break;
				case 0:

					cout << (j+1);
					break;
			}
		}
		input %= (int)pow(10.0,i);
	}
	//要输出endl么？

	return 0;
}