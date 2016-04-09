#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

#define MAX 25

using namespace std;

int main()
{
	char num[MAX],result[MAX];
	int in=0;

	scanf("%s",num);
	for(int i=strlen(num)-1;i>=0;i++){
		int temp = (num[i]-'0')*2;
		result[i] = temp%10+in+'0';
		in = temp/10;
	}

}