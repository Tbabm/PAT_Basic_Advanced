#include <stdio.h>

#define MAX 1001
#define MAX2 22

int main(){
	double poly[MAX];
	int index[MAX2];

	//此处应该可以使用memcpy
	for(int i=0;i<MAX;i++)
		poly[i] = 0;

	int k;
	for(int j=0;j<2;j++){
		scanf("%d",&k);
		for(int i=0;i<k;i++){
			int ex;
			double co;
			scanf("%d %lf",&ex,&co);
			poly[ex] += co;
		}
	}

	int count = 0;
	for(int i=0;i<MAX;i++){
		if(poly[i] != 0){
			index[count++] = i;
		}
	}

	printf("%d",count);
	for(int i=count-1;i>=0;i--)
		printf(" %d %0.1lf",index[i],poly[index[i]]);

	printf("\n");
}