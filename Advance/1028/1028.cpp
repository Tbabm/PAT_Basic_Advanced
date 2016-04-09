// records <= 100000
// id 6
// name：最多8位，没有空格
// 成绩 0-100

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

#define MAX_STU 100005
#define MAX_ID 8
#define MAX_NAME 10

using namespace std;
struct student
{
	char id[MAX_ID];
	char name[MAX_NAME];
	int grade;
} stus[MAX_STU];

bool cmp1(struct student a,struct student b)
{
	return strcmp(a.id,b.id)<0;
}

bool cmp2(struct student a,struct student b)
{
	if(strcmp(a.name,b.name) == 0)
		return strcmp(a.id,b.id)<0;
	else
		return strcmp(a.name,b.name)<0;
}

bool cmp3(struct student a,struct student b)
{
	if(a.grade == b.grade)
		return strcmp(a.id,b.id)<0;
	else
		return a.grade<b.grade;
}


int main()
{
	int num,col;
	scanf("%d %d",&num,&col);

	for(int i=0;i<num;i++)
		scanf("%s %s %d",stus[i].id,stus[i].name,&stus[i].grade);

	if(col == 1)
		sort(stus,stus+num,cmp1);
	else if(col == 2)
		sort(stus,stus+num,cmp2);
	else
		sort(stus,stus+num,cmp3);

	for(int i=0;i<num;i++)
	{
		printf("%s %s %d\n",stus[i].id,stus[i].name,stus[i].grade);
	}

	return 0;
}