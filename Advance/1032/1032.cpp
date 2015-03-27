// 3个测试点过不了，暂时不知道原因

#include <iostream>
#include <vector>

using namespace std;

class Node{
public:
	int id;
	int times;
};

vector<Node> nodes;

int find(int id){
	for (size_t i = 0; i < nodes.size(); i++){
		if (id == nodes[i].id)
			return i;
	}
	return -1;
}

int main(){
	Node start1, start2;
	int n;
	scanf("%d %d %d", &(start1.id), &(start2.id), &n);
	start1.times = 1;
	start1.times = 1;
	nodes.push_back(start1);
	nodes.push_back(start2);

	for (int i = 0; i < n; i++){
		Node s, e;
		char ch;
		scanf("%d %c %d", &(s.id), &ch, &(e.id));
		int index = find(e.id);
		if (index != -1){
			nodes[index].times += 1;
			if(nodes[index].id != -1)
				printf("%05d\n",nodes[index].id);
			else
				printf("%d\n",nodes[index].id);
			break;
		}
		else{
			e.times = 1;
			nodes.push_back(e);
		}
	}

	// for (size_t i = 0; i < nodes.size(); i++){
	// 	if (nodes[i].times == 2)
	// 		printf("%d\n", nodes[i].id);
	// }

	return 0;
}