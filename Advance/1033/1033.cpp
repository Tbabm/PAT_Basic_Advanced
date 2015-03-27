// 1.题目只说是正数，并没有说是正整数，所以，除了index和数量，其余都要用double来表示！
// 2.多层数组要细心，不要少写[]
// 3.采用vector存放各站的举例，使用sort排序，便于查找，然后使用map存储各站的价格！

// 如何解此题：
// 1.首先，这种几乎想不出已有算法的题目一般都需要考贪心解决，要有这种觉悟
// 2.如何解决贪心问题：
// 		1.先使用贪心法，手动地走一遍所有样例
// 		2.归纳总结出所有的变量，比如此题的变量就是，1）终点是否在可到达的范围内，2）该范围内是否有加油站，
// 		  3）加油站中是否有价格低于当前加油站的
// 		3.然后分别讨论各种情况
// 		4.最后考虑特殊情况

// 本题的情况：
// 1.终点不在可到达范围，600米内（含，下同）没有加油站 -> 不能到达，当前距离+600为最大距离（针对样例，下同），
//   循环结束。
// 2.终点不在可到达范围内，600米内有站，有比当前便宜的-> 加油到足够跑到第一个比当前便宜的加油站
// 3.终点不在可到达范围内，600米内有站，没有比当前便宜的 -> 找到最便宜的那个,加满油,跑到那个加油站
// 4.终点在可到达范围内，该范围内（不含，下同）有站，且有比当前便宜 -> 处理方式同2
// 5.终点在可到达范围内，该范围内（不含，下同）没有站，或者没有比当前便宜 -> 直接加油到正好可以到终点，循环结束

// 特殊情况:
// 1.起点没有加油站
// 2.起点就是终点（测试样例中没有这个）

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define MAX 500000.0

vector<double> stations;
map<double, double> prices;

int findStation(int begin,double reach){
	int i;
	if (begin + 1 == stations.size() || stations[begin + 1] > reach)
		return -1;		//没站了

	bool flag = false;
	double minPri = prices[stations[begin + 1]];
	int minIndex = begin + 1;
	for (i = begin + 1; i < stations.size() && stations[i] <= reach;i++){
		if (prices[stations[i]] <= prices[stations[begin]]){
			flag = true;
			break;
		}
		if (prices[stations[i]] < minPri){
			minPri = prices[stations[i]];
			minIndex = i;
		}
	}
	
	if (flag)
		return i;				//有便宜的站
	else
		return minIndex;			//没有便宜的站
}

int findStation2(int begin, double reach){
	int i;
	if (begin + 1 == stations.size() || stations[begin + 1] >= reach)
		return -1;		//没站了

	double minPri = prices[stations[begin + 1]];
	int minIndex = begin + 1;
	for (i = begin + 1; i < stations.size() && stations[i] < reach; i++){
		if (prices[stations[i]] <= prices[stations[begin]]){
			break;
		}
		if (prices[stations[i]] < minPri){
			minPri = prices[stations[i]];
			minIndex = i;
		}
	}

	return i;			//有站
}

int main(){
	double Cap, Dis, Davg;
	int Num;
	scanf("%lf %lf %lf %d", &Cap, &Dis, &Davg, &Num);

	for (int i = 0; i < Num; i++){
		double pri;
		double distance;
		scanf("%lf %lf", &pri, &distance);
		stations.push_back(distance);
		prices[distance] = pri;
	}

	sort(stations.begin(), stations.end());
	
	double total = 0;
	int curIndex = 0;
	double leftDis = 0;
	double farDis = 0;
	bool flag = true;
	
	if (stations[0] != 0)
		flag = false;

	while (flag){
		double canReach = stations[curIndex] + Cap*Davg;
		if (canReach < Dis){		//到不了
			int next = findStation(curIndex,canReach);
			if (next == -1){		//没站了
				flag = false;
				farDis = canReach;
				break;
			}
			else if (prices[stations[next]] > prices[stations[curIndex]]){	//后面的站都比现在的贵
				//加满油
				total += (Cap - leftDis / Davg)*prices[stations[curIndex]];
				//行驶到最便宜的那个地方
				leftDis = Cap*Davg - (stations[next] - stations[curIndex]);
				curIndex = next;
			}
			else{	//后面有便宜的
				//加到够就行
				//余油一定不能走到最近的比当前便宜的地方
				total += (stations[next] - stations[curIndex] - leftDis) / Davg*prices[stations[curIndex]];
				leftDis = 0;
				curIndex = next;
			}
		}
		else{
			int next = findStation2(curIndex, Dis);
			if (next == -1 || prices[stations[next]] > prices[stations[curIndex]]){
				//没站，或者后面的站都比现在的贵
				//走到了
				total += (Dis - stations[curIndex] - leftDis) /Davg * prices[stations[curIndex]];
				leftDis = 0;
				break;
			}
			else{
				//加到刚好够
				total += (stations[next] - stations[curIndex] - leftDis) / Davg*prices[stations[curIndex]];
				leftDis = 0;
				curIndex = next;
			}
		}
	}

	if (flag)
		printf("%.2lf\n", total);
	else
		printf("The maximum travel distance = %.2lf\n", farDis);

	//system("pause");
	return 0;
}