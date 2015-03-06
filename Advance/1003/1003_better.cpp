//使用二维数组存储地图，使用一个struct数组存储城市信息
//main中进行输入输出，另开一个函数实现算法！

#include <iostream>

using namespace std;

#define MAX_CITY 501
#define INF 	 0x7FFFFFFF
#define NAV	     -1

int map[MAX_CITY][MAX_CITY];

struct City{
	bool know;
	int	 dist;
	int	 teamNum;
	int  teams;
	int  ways;
} cities[MAX_CITY];

int findMin(int cityNum){
	int min = INF;
	int index = NAV;

	for(int i=0;i<cityNum;i++){
		if(!cities[i].know && cities[i].dist<min){
			min = cities[i].dist;
			index = i;
		}
	}	

	return index;

}

void dijkstra(int start,int end,int cityNum){
	while(1){
		//find unknown city with min dist
		int index = findMin(cityNum);
		if(index == NAV || index == end)
			break;
		cities[index].know = true;
		for(int i=0;i<cityNum;i++){
			if(!cities[i].know && map[index][i] != INF){
				if(cities[index].dist + map[index][i] < cities[i].dist){
					cities[i].dist = cities[index].dist + map[index][i];
					cities[i].ways = cities[index].ways;
					cities[i].teams = cities[index].teams+cities[i].teamNum;
				}
				else if(cities[index].dist + map[index][i] == cities[i].dist){
					cities[i].ways += cities[index].ways;
					if(cities[index].teams+cities[i].teamNum > cities[i].teams)
						cities[i].teams = cities[index].teams+cities[i].teamNum;		
				}
			}
		}
	}
}

int main(){
	int cityNum,roadNum,start,end;

	cin >> cityNum >> roadNum >> start >> end;

	for(int i=0;i<cityNum;i++){
		cin >> cities[i].teamNum;
		cities[i].know = false;
		cities[i].dist = INF;
		cities[i].teams = 0;
		cities[i].ways = 0;
	}

	for(int i=0;i<cityNum;i++){
		for(int j=0;j<cityNum;j++)
			map[i][j] = INF;
	}

	cities[start].dist = 0;	
	cities[start].teams = cities[start].teamNum;
	cities[start].ways = 1;

	for(int i=0;i<roadNum;i++){
		int x,y;
		cin >> x >> y;
		cin >> map[x][y];
		map[y][x] = map[x][y];
	}

	dijkstra(start,end,cityNum);

	cout << cities[end].ways << " " << cities[end].teams << endl;

	return 0; 
}