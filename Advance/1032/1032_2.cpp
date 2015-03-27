// 采用数组来存储链表,Hash思想的应用

// 问题：
// 1.不能用STL，会超时
// 2.如果输入的格式中，位数是确定的，那么输出的格式中也要注意位数对齐。精度也同理。

#include <iostream>
#include <cstring>

using namespace std;

#define MAX 100000

int list[MAX];
bool visit[MAX];

int main(){
	int start1, start2, num;
	scanf("%d %d %d", &start1, &start2, &num);

	memset(visit, false, MAX*sizeof(bool));
	for (int i = 0; i<num; i++){
		int id1, id2;
		char ch;
		scanf("%d %c %d", &id1, &ch, &id2);
		list[id1] = id2;
	}

	int temp1 = start1;
	while (temp1 != -1){
		visit[temp1] = true;
		temp1 = list[temp1];
	}
	
	int temp2 = start2;
	while (temp2 != -1){
		if (visit[temp2]){
			// make sure that it is 5-digit
			printf("%05d\n", temp2);
			break;
		}
		temp2 = list[temp2];
	}
	
	if (temp2 == -1)
		printf("-1\n");
	
	// system("pause");
	return 0;
}