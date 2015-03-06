// 本题是一道经典的算法题，一共有三种解法：
// 1.直接循环，O(n^2)的时间复杂度。
// 2.采用分治法，O(NlogN)的时间复杂度。
// 3.动态规划，O(N)的时间复杂度。
// 事实证明，是不是long long并没有关系
// 初始化的问题，永远先从自己的代码中找逻辑错误！
// 出错的case
// 1
// 10


#include <iostream>

using namespace std;

int main(){
	int n;
	cin >> n;
	int seq[n];
	int begin,end,curBeg,curEnd;
	// 修改成了long long，但是貌似没用
	long long maxSeq,curSeq;

	cin >> seq[0];
	maxSeq = curSeq = seq[0];
	// 第一次的时候忘了初始化begin 和 end
	// 尽量用统一的流程去做，不然很容易考虑漏
	begin = end = curBeg = curEnd = seq[0];
	for(int i=1;i<n;i++){
		cin >> seq[i];
		
		if(curSeq <=0){
			curSeq = seq[i];
			curBeg = curEnd = seq[i];
		}
		else{
			curSeq += seq[i];
			curEnd = seq[i];
		}

		if(curSeq > maxSeq){
			maxSeq = curSeq;
			begin = curBeg;
			end = curEnd;
		}
	}

	if(maxSeq < 0){
		maxSeq = 0;
		begin = seq[0];
		end = seq[n-1];
	}

	cout << maxSeq << " " << begin << " " << end << endl;

	return 0;
}