#include <stdio.h>

#define AMOUNT 5

int main(){
	int a,b,result,absre;
	scanf("%d %d",&a,&b);
	result = a+b;
	absre = result>0?result:-result;

	int num[AMOUNT];
	int i = 0;

	do{
		num[i++] = absre%1000;
		absre /= 1000;
	}while(absre);

	if(result < 0)
		printf("-");

	printf("%d",num[i-1]);

	for(i-=2;i>=0;i--)
		printf(",%03d",num[i]);

	printf("\n");

	return 0;
}