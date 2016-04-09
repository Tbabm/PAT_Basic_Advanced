/*
several erros:
1. forget print No if strcmp != 0
2. forget add '\0' to d_num
3. we must consider carry? WTF?
   read the problem!!!!!we must print double_num even print No!!!!!!! 
   So, we must get the carry, and print it if neccessary
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#define MAX 25

using namespace std;

int double_num(char num[], char d_num[]){
	int i,flag=0;
	int length = strlen(num);

	for(i=length-1;i>=0;i--){
		int d_digit;
		d_digit = (int)(num[i]-'0')*2 + flag;
		flag = d_digit/10;
		d_num[i] = d_digit%10 + '0';
	}

	d_num[length] = '\0';
	if(flag)
		return 1;
	else
		return 0;
}

int main(){
	char num[25],d_num[25];

	scanf("%s",num);

	if(double_num(num, d_num))
		printf("No\n1%s\n",d_num);
	else{
		int length = strlen(num);
		char result_num[25];
		sort(num,num+length);
		strcpy(result_num, d_num);
		sort(d_num,d_num+length);
		if(strcmp(num,d_num) == 0)
			printf("Yes\n");
		else
			printf("No\n");
		printf("%s\n",result_num);
	}

	return 0;
}