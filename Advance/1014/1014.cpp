#include <iostream>
#include <queue>
#include <stdio.h>

#define MAX_WINDOWS 22
#define MAX_CAPACITY 12
#define MAX_CUSTOMER 1002

using namespace std;

int main(){
    int times[MAX_CUSTOMER],queries[MAX_CUSTOMER],finish[MAX_CUSTOMER];
    int n,m,k,q,i,j;
    queue<int> queues[MAX_WINDOWS];

    cin >> n >> m >> k >> q;
    
    for(i=0;i<k;i++)
        cin >> times[i];
    for(i=0;i<q;i++)
        cin >> queries[i];

    for(i=0;i<k;i++)
        finish[i]=-1;

    int count = 0;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(count >= k)
                break;
            else
                queues[j].push(count++);
        }
    }

    for(i=1;i<=9*60;i++){
        for(j=0;j<n;j++){
            if(queues[j].size() == 0)
                continue;
            times[queues[j].front()] -= 1;
            if(times[queues[j].front()] <= 0){
                finish[queues[j].front()] = i;
                queues[j].pop();
                if(count < k)
                    queues[j].push(count++);
            }           
       }
    }
    
    // for(i=0;i<=9*60;i++){
    //     for(j=0;j<n;j++){
    //         while(queues[j].size() > 0 && times[queues[j].front()] <= 0){
    //             finish[queues[j].front()] = i;
    //             queues[j].pop();
    //             if(count < k)
    //                 queues[j].push(count++);
    //         }
    //         if(queues[j].size() <=0)
    //             continue;
    //         times[queues[j].front()] -= 1;     
    //    }
    // }

    for(i=0;i<q;i++){
        if(finish[queries[i]-1] == -1)
            cout << "Sorry" << endl;
        else{
            int hours = finish[queries[i]-1]/60 + 8;
            int mins = finish[queries[i]-1]%60;
                    
            printf("%02d:%02d\n",hours,mins);   
        }
    }

    return 0;
}


// 终于搞清楚了我这个思路的漏洞在哪里

// 没能在17:00之前得到服务的才会打Sorry，而不是17:00之前不能服务完成的！
// 因为无法预估其最后完成时间，所以这种思路是有缺陷的，不是最简单的方法
