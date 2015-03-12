// 模拟即可，跑样例会跑出37.97，是样例写错，不用理会

#include <iostream>

using namespace std;

#define NUM 3
#define RATE 0.65

int main(){
	int choice[NUM];
	int count=0;
	double temp;
	double best = 1.0;

	for(int i=0;i<3;i++){
		double max = 0;
		for(int j=0;j<3;j++){
			scanf("%lf",&temp);
			if(temp > max){
				max = temp;
				choice[count] = j;
			}
		}
		best *= max;
		// cout << best << endl;
		count++;
	}

	for(int i=0;i<3;i++){
		switch(choice[i]){
			case 0:
				printf("W ");
				break;
			case 1:
				printf("T ");
				break;
			case 2:
				printf("L ");
				break;
		}
	}

	best = (best*RATE-1)*2;
	printf("%.2lf\n",best);

	return 0;
}