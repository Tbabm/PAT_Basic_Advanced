#include<cstdio>  
#include<cstring>  
#include<cmath>  
#include<string>  
#include<vector>  
#include<map>  
#include<set>  
#include<queue>  
#include<algorithm>  
using namespace std;  
#define INF 0x6fffffff  
struct customer  
{  
    int wasteTime;//所需时间  
    int sTime;//开始时间  
    int eTime;//结束时间  
}cust[1005];  
struct window  
{  
    int eTime;//窗口处理完的时间  
    queue<int> q;  
}win[25];  
int main()  
{  
    int n,m,k,q,i=1;  
    int minTime,idx,pos;  
    scanf("%d%d%d%d",&n,&m,&k,&q);  
    for(i=1;i<=k;++i)  
        scanf("%d",&cust[i].wasteTime);  
    i=1;  
    for(int j=0;i<=n*m&&i<=k;++i,j=(j+1)%n)  
    {  
        cust[i].sTime=win[j].eTime;//客户开始时间等于当前窗口结束时间  
        cust[i].eTime=win[j].eTime+cust[i].wasteTime;//计算客户结束时间  
        win[j].eTime+=cust[i].wasteTime;//修正当前窗口结束时间  
        win[j].q.push(i);  
    }  
    for(;i<=k;++i)  
    {  
        minTime=INF;  
        for(int j=0;j<n;++j)  
        {  
            idx=win[j].q.front();  
            if(minTime>cust[idx].eTime)  
            {  
                minTime=cust[idx].eTime;  
                pos=j;  
            }  
        }  
        cust[i].sTime=win[pos].eTime;  
        cust[i].eTime=win[pos].eTime+cust[i].wasteTime;  
        win[pos].eTime+=cust[i].wasteTime;  
        win[pos].q.pop();  
        win[pos].q.push(i);  
    }  
    int hour,mintus;  
    for(;q--;)  
    {  
        scanf("%d",&k);  
        if(cust[k].sTime+8*60>=17*60)  
            printf("Sorry\n");  
        else  
        {  
            hour=(cust[k].eTime+8*60)/60;  
            mintus=(cust[k].eTime+8*60)%60;  
            if(hour>=10)  
                printf("%d:",hour);  
            else  
                printf("0%d:",hour);  
            if(mintus>=10)  
                printf("%d\n",mintus);  
            else  
                printf("0%d\n",mintus);  
        }  
    }  
    return 0;  
}  