/*
*标准30分题：Dijstra+各种各样的信息
*1. 找最短路径：Dijstra算法，找最短，标记，更新路径：循环n次
*2. 找最短路径条数：到rome的最短路径条数是到rome的pre的所有最短路径条数之和。所以用的是+，不是乘！切记！
*	<：最短路径条数更新成pre的最短路径条数，切记是pre！
*	=：原有最短路径条数+pre最短路径条数
*3. 找其中happiness最高的：记录一个变量，像cost一样更新即可。
*4. 如果一样高，找hapiness average最高的：记录city_sum，像cost一样更新即可
*5. 记录路上的点：维护一个pre数组，像cost一样更新即可。
*/


#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <stack>

#define MAX 205
#define INF 0x7FFFFFFF

using namespace std;

int n,k,rome;
map<string,int> name;
string indexes[MAX];
int cities[MAX][MAX];
int hap[MAX],known[MAX],dist[MAX],hap_sum[MAX],ci_num[MAX],pre[MAX],ways[MAX]={0};

void dijstra(){
	for(int i=0;i<n;i++){
		known[i] = 0;
		dist[i] = INF;
	}

	dist[0] = 0;
	hap_sum[0] = 0;
	ci_num[0] = 0;
	pre[0] = -1;
	ways[0] = 1;

	for(int i=0;i<n;i++){
		int minDist = INF;
		int pos = -1;
		for(int j=0;j<n;j++){
			if(!known[j] && dist[j]<minDist){
				minDist = dist[j];
				pos = j;
			}
		}

		known[pos] = 1;

		for(int j=0;j<n;j++){
			// 更新距离
			if(!known[j] && cities[pos][j]!=-1){
				if(cities[pos][j]+dist[pos] < dist[j]){
					dist[j] = cities[pos][j] + dist[pos];
					hap_sum[j] = hap_sum[pos]+hap[j];
					ci_num[j] = ci_num[pos]+1;
					pre[j] = pos;
					ways[j] = ways[pos];
				}
				else if(cities[pos][j]+dist[pos] == dist[j]){
					ways[j]+=ways[pos];
					if(hap_sum[pos] + hap[j] > hap_sum[j]){
						hap_sum[j] = hap_sum[pos]+hap[j];
						ci_num[j] = ci_num[pos]+1;
						pre[j] = pos;
					}
					else if(hap_sum[pos] + hap[j] == hap_sum[j] && ci_num[pos]+1 < ci_num[j]){
						ci_num[j] = ci_num[pos]+1;
						hap_sum[j] = hap_sum[pos]+hap[j];
						pre[j] = pos;
					}
				}
			}
		}
	}
}

int main()
{
	// 总是假设起点为0
	string start;
	cin >> n >> k >> start;
	name[start] = 0;
	indexes[0] = start;
	hap[0] = 0;

	for(int i=1;i<n;i++){
		string temp;
		cin >> temp >> hap[i];
		if(temp == "ROM")
			rome = i;
		name[temp] = i;
		indexes[i] = temp;
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cities[i][j] = -1;
		}
	}

	for(int i=0;i<k;i++){
		string city1,city2;
		int cost;
		cin >> city1 >> city2 >> cost;
		cities[name[city1]][name[city2]] = cities[name[city2]][name[city1]] = cost;
	}

	dijstra();

	int cur = rome;
	stack<string> ans;

	while(cur != -1){
		ans.push(indexes[cur]);
		cur = pre[cur];
	}

	printf("%d %d %d %d\n",ways[rome],dist[rome],hap_sum[rome],hap_sum[rome]/ci_num[rome]);

	cout << ans.top();
	ans.pop();
	while(!ans.empty()){
		cout << "->" << ans.top();
		ans.pop();
	}
	cout << endl;

	return 0;
}