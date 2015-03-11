// use list to store the polynomial
// 构造数据测试：
// 1.特殊情况，K=0,虽然题目并未要求;
// 2.边界值，比如Ni = 1000;

// 犯的错误：
// 1.MAX最开始设置为了202，但是result的最大指数可能达到2002
// 2.遍历result数组是，i初始化成了MAX，而非MAX-1，导致result[2002]不存在也被遍历了，使答案错误

#include <iostream>
#include <vector>

using namespace std;

//this should be 2000!not 202
#define MAX 2002
#define MAXPOS 102

class Poly{
public:
	int expo;
	double coe;

	Poly(int _expo,double _coe){
		expo = _expo;
		coe = _coe;
	}
};

vector<Poly> x;
vector<Poly> y;
//attention:you'd better not use {0} to init here
double result[MAX];
int pos[MAXPOS];

void initPoly(vector<Poly> &mult,int n){
	for(int i=0;i<n;i++){
		int expo;
		double coe;
		scanf("%d %lf",&expo,&coe);
		Poly temp(expo,coe);
		mult.push_back(temp);
	}
}

void multPoly(){
	for(int i=0;i<x.size();i++){
		for(int j=0;j<y.size();j++){
			result[x[i].expo+y[j].expo] += x[i].coe*y[j].coe;
		}
	}
}

int main(){
	int n;
	int count=0;
	scanf("%d",&n);
	initPoly(x,n);
	scanf("%d",&n);
	initPoly(y,n);

	for(int i=0;i<MAX;i++)
		result[i] = 0.0;

	for(int i=0;i<MAXPOS;i++)
			pos[i] = -1;

	multPoly();

	for(int i=MAX-1;i>=0;i--){
		if(result[i] != 0.0)
			pos[count++] = i;
	}

	printf("%d",count);
	for(int i=0;i<count;i++)
		printf(" %d %0.1lf",pos[i],result[pos[i]]);
	printf("\n");

	return 0;

}
