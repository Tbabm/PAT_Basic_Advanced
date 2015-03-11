// 修正之前错误，采用二分法解决

// 基数不能为1

#include <iostream>
//包含strcpy!
#include <cstring>
#include <string>

using namespace std;

#define MAX 11

int char2Int(char ch){
	if(ch>='0' && ch<='9')
		return ch-'0';
	else if(ch>='a' && ch<='z')
		return ch-'a'+10;

	return 0;
}

long long getValue(char* num,long long radix,int len){
	long long value = 0;
	for(int i=0;i<len;i++){
		value *= radix;
		value += char2Int(num[i]);

		if(value < 0)
			return -1;
	}

	return value;
}

int main(){
	char num1[MAX],num2[MAX],temp[MAX];
	int tag;
	long long radix1,radix2,value1,value2;

	scanf("%s %s %d %lld",num1,num2,&tag,&radix1);

	//first is dest,second is unknown
	if(tag == 2){
		strcpy(temp,num1);
		strcpy(num1,num2);
		strcpy(num2,temp);
	}

	value1 = getValue(num1,radix1,strlen(num1));

	//二分法找radix2

	//需要 long long，因为可能很大！
	long long low = 0;
	for(int i=0;i<strlen(num2);i++){
		int tempInt = char2Int(num2[i]);
		if(tempInt > low)
			low = tempInt;
	}

	low += 1;

	long long high = value1 + 1;

	bool flag = false;
	while(low <= high){
		radix2 = (low+high)/2;
		value2 = getValue(num2,radix2,strlen(num2));
		if(value2 == -1 | value2 > value1)
			high = radix2-1;
		else if(value2 < value1)
			low = radix2+1;
		else{
			flag = true;
			break;
		}
	}

	if(flag)
		printf("%lld\n",radix2);
	else
		printf("Impossible\n");

}