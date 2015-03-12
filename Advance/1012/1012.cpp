// 1.平均成绩需要四舍五入，除代码中的方法外，也可采用/3.0+0.5，然后转换为int的方法
// 2.sort默认为升序！注意排序的顺序！
// 3.注意注释掉cout！
// 4.switch可以通过建立查找表来简单实现。

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 2002

class Student{
public:
	int name;
	int a;
	int c;
	int m;
	int e;
};

vector<Student> stus;
vector<int> AVE,CL,MA,EN;

int getRank(vector<int> &v,int g){
	for(size_t i=0;i<v.size();i++){
		if(g == v[i])
			return i+1;
	}

	return -1;
}

int main(){
	int N,M;

	scanf("%d %d",&N,&M);
	for(int i=0;i<N;i++){
		Student stu;
		scanf("%d %d %d %d",&stu.name,&stu.c,&stu.m,&stu.e);
		
		int total = stu.c + stu.m + stu.e;
		// 也可以/3.0+0.5，然后强制转换为int
		stu.a = total/3;
		if(total%3 == 2)
			stu.a += 1;
		AVE.push_back(stu.a);
		CL.push_back(stu.c);
		MA.push_back(stu.m);
		EN.push_back(stu.e);
		stus.push_back(stu);
	}

	sort(AVE.begin(),AVE.end(),greater<int>());
	sort(CL.begin(),CL.end(),greater<int>());
	sort(MA.begin(),MA.end(),greater<int>());
	sort(EN.begin(),EN.end(),greater<int>());

	for(int k=0;k<M;k++){
		int id,min,minIndex;
		int rank[4];
		scanf("%d",&id);

		int index = -1;
		for(size_t j=0;j<stus.size();j++){
			if(stus[j].name == id){
				index = j;
				break;
			}
		}
		if(index == -1)
			printf("N/A\n");
		else{
			// 0-3:a c m e
			rank[0] = getRank(AVE,stus[index].a);
			rank[1] = getRank(CL,stus[index].c);
			rank[2] = getRank(MA,stus[index].m);
			rank[3] = getRank(EN,stus[index].e);

			// cout << stus[index].a << " " << stus[index].c << " " << stus[index].m << " " << stus[index].e <<endl;			
			// cout << rank[0] << " " << rank[1] << " " << rank[2] << " " << rank[3] <<endl;
			min = rank[0];
			minIndex = 0;
			for(int i=1;i<4;i++){
				if(rank[i] < min){
					min = rank[i];
					minIndex = i;
				}
			}

			// 可使用查找表来简化数组！
			switch(minIndex){
				case 0:
					printf("%d A\n",min);
					break;
				case 1:
					printf("%d C\n",min);
					break;
				case 2:
					printf("%d M\n",min);
					break;
				case 3:
					printf("%d E\n",min);
					break;
			}

		}

	}

}