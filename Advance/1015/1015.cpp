// 考虑prime = 0或1这两种特殊情况

#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

#define MAX 20

int getRePrime(int prime,int radix){
	int value = 0;
	while(prime){
		value *= radix;
		value += prime%radix;
		prime /= radix;
	}

	return value;
}

bool isPrime(int num){
	int upper = sqrt(num);
	bool flag = true;
	if(num == 0 | num == 1)
		flag = false;
	for(int i=2;i<=upper;i++){
		if(num%i == 0){
			flag = false;
			break;
		}
	}

	return flag;
}

int main(){
	int prime,rePrime,radix;
	scanf("%d",&prime);
	while(prime >= 0){
		scanf("%d",&radix);
		rePrime = getRePrime(prime,radix);
		if(isPrime(prime) && isPrime(rePrime))
			printf("Yes\n");
		else
			printf("No\n");

		scanf("%d",&prime);
	}

	return 0;
}