// 利用Dijkstra算法解决，注意最短路径数量的计算和权重和的计算
// 遇到的问题
// 1.设置最大整数的时候：如果使用的是int，那么需要用0x7FFFFFFF，而不是0xFFFFFFFF
// 2.起点初始化的时候不能设置为know，因为循环中找的对象是未知点
// 3.增加最短路径数量的时候，需要加pre点的路径数量，而非1！！！

#include <iostream>

using namespace std;

#define NAV -1
//problem 1：for int,0xFFFFFFFF means -1
#define INF 0x7FFFFFFF

class List{
public:
	int index;
	int value;
	List* next;

	List(){
		index = -1;
		value = 0;
		next = NULL;
	}
};

class City{
public:
	List* header;
	bool know;
	int dist;
	int teamNum;
	int ways;
	int teams;

	City(){
		header = NULL;
		know = false;
		dist = INF;
		ways = 0;
		teams = 0;
	}

	void init(){
		//problem 2:it should be know when findMin
		//know = true;
		dist = 0;
		ways = 1;
		teams = teamNum;
	}

	void updateList(int adj,int value){
		if(header == NULL){	
			header = new List;
			header->index = adj;
			header->value = value;
		}
		else{
			List *temp = header;
			while(temp->next != NULL)
				temp = temp->next;

			temp->next = new List;
			temp->next->index = adj;
			temp->next->value = value;

		}
	}
};

int findMinDist(City* cities,int cityNum);

int main(){
	int cityNum,roadNum,start,end;

	//scanf("%d %d %d %d",&cityNum,&roadNum,&start,&end);
	cin >> cityNum >> roadNum >> start >> end;	

	City *cities = new City[cityNum];
	for(int i=0;i<cityNum;i++)
		cin >> cities[i].teamNum;
	cities[start].init();

	for(int i=0;i<roadNum;i++){
		int s,d,t;
		cin >> s >> d >> t;

		cities[s].updateList(d,t);
		cities[d].updateList(s,t);
		
	}

	while(1){
		int indexOfMin = findMinDist(cities,cityNum);
		if(indexOfMin == NAV || indexOfMin == end)
			break;
		City *tempCity = &(cities[indexOfMin]);
		tempCity->know = true;
		List *tempHeader = tempCity->header;
		while(tempHeader != NULL){
			int tempIndex = tempHeader->index;
			if(!cities[tempIndex].know){
				if(tempCity->dist + tempHeader->value < cities[tempIndex].dist){
					cities[tempIndex].dist = tempCity->dist + tempHeader->value;
					cities[tempIndex].ways = tempCity->ways;
					cities[tempIndex].teams = tempCity->teams + cities[tempIndex].teamNum;
				}
				else if(tempCity->dist + tempHeader->value == cities[tempIndex].dist){
					cities[tempIndex].ways += tempCity->ways;	//the right hand is ways ,not 1!!!
					if(tempCity->teams + cities[tempIndex].teamNum > cities[tempIndex].teams)
						cities[tempIndex].teams = tempCity->teams + cities[tempIndex].teamNum;	
				}
			}
			tempHeader = tempHeader->next;
		}
	}

	cout << cities[end].ways << " " << cities[end].teams << endl;

	delete[] cities;

	return 0;
}

int findMinDist(City* cities,int cityNum){
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