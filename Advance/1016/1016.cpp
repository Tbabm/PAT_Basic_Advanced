#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

#define MAX_REC_NUM 1005
#define MAX_RATE_NUM 25

struct record
{
	char name[25];
	int mon;
	int day;
	int hour;
	int min;
	bool state;
} rec[MAX_REC_NUM];

int rate[MAX_RATE_NUM];
int n;

bool cmp(struct record a, struct record b)
{
	if(strcmp(a.name,b.name) != 0)
		return strcmp(a.name,b.name)<0;
	if(a.mon != b.mon)
		return a.mon < b.mon;
	if(a.day != b.day)
		return a.day < b.day;
	if(a.hour != b.hour)
		return a.hour < b.hour;
	if(a.min != b.min)
		return a.min < b.min;
	else
		return 0;

}

bool check(int st)
{
	int i;
	bool flag=0,out=0;

	for(i=st;i<n;i++)
	{
		//名字变了
		if(strcmp(rec[st].name,rec[i].name) != 0)
			break;
		if(rec[i].state == 1)
			flag = 1;
		else if(flag){
			flag = 0;
			out = 1;
			break;
		}
	}

	return out;
}

int calTime(int st,int en)
{
	int stMin=0,enMin=0;

	stMin = rec[st].day*24*60 + rec[st].hour*60 + rec[st].min;
	enMin = rec[en].day*24*60 + rec[en].hour*60 + rec[en].min;

	return enMin - stMin;
}

int calFee(int st,int en)
{
	int day = rec[st].day;
	int hour = rec[st].hour;
	int min = rec[st].min;
	int dmin =0;

	int fee = 0;

	int dayfee = 0;
	for(int i=0;i<24;i++)
		dayfee += rate[i]*60;


	// 处理分针
	if(rec[st].day == rec[en].day && rec[st].hour == rec[en].hour)
	{
		// 细心！下面需要dmin，所以不能把dmin注释掉！
		dmin = rec[en].min - rec[st].min;
		fee += rate[hour] * dmin;
	}
	else
	{
		// dmin = 60-min + rec[en].min;
		fee += rate[hour] * (60-min) + rate[rec[en].hour] * rec[en].min;
		hour++;
		
		// 处理时针
		if(hour > rec[en].hour)
		{
			// dhour = 24+rec[en].hour-hour;
			fee += dayfee;
			for(int i=rec[en].hour;i<hour;i++)
				fee -= rate[i]*60;
			day += 1;
		}
		else if(hour < rec[en].hour)
		{
			// dhour = rec[en].hour - hour;
			for(int i=hour;i<rec[en].hour;i++)
				fee += rate[i]*60;
		}

		// 处理天
		fee += (rec[en].day - day) * dayfee;
	}

	return fee;
	
}

int main()
{
	int i;
	char tempState[10];

	for(i=0;i<24;i++)
		scanf("%d",rate+i);
	scanf("%d",&n);

	for(i=0;i<n;i++)
	{
		scanf("%s",rec[i].name);
		scanf("%d:%d:%d:%d" , &(rec[i].mon) , &(rec[i].day) , &(rec[i].hour) , &(rec[i].min));
		scanf("%s",tempState);
		rec[i].state = (tempState[1]=='n')?1:0;
	}

	sort(rec,rec+n,cmp);
	
	//debug
	// int temp1=2,temp2=3;
	// cout << "2:" << endl;
	// cout << rec[temp1].name << " " << rec[temp1].hour << " " << rec[temp1].min << " " << rec[temp1].state << endl;
	// cout << "3:" << endl;
	// cout << rec[temp2].name << " " << rec[temp2].hour << " " << rec[temp2].min << " " << rec[temp2].state << endl;
 

	for(i=0;i<n;i++)
	{
		bool out=0;
		out = check(i);

		//一个人一个人地处理
		if(out)
		{
			char curName[25];
			int curOn = i;
			strcpy(curName,rec[i].name);

			bool flag = 0;
			int totalFee = 0;

			printf("%s %02d\n",rec[i].name,rec[i].mon);
			for(;strcmp(curName,rec[i].name)==0;i++)
			{
				int curFee = 0,curTime=0;
				if(rec[i].state)
				{
					flag = 1;
					curOn = i;
				}
				else if(flag)
				{
					flag = 0;
					printf("%02d:%02d:%02d %02d:%02d:%02d ",rec[curOn].day,rec[curOn].hour,rec[curOn].min,rec[i].day,rec[i].hour,rec[i].min);
					curTime = calTime(curOn,i);
					curFee = calFee(curOn,i);
					printf("%d $%.2f\n",curTime,(double)curFee/100);
					totalFee += curFee;	
				}
			}
			//现在换了个人了！所以要减掉，不然加了两次
			i--;
			printf("Total amount: $%.2f\n",(double)totalFee/100);
		}
	}

	return 0;
}