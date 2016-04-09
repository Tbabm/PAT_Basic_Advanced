// 务必细心，有问题首先想参数！
// 很有可能连example的执行过程都不是全对的，只是凑巧得出了这个答案。
// 所以，实在没招的时候先跟一遍example，看看是不是真的是OK的。

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>

#define MAX 85

using namespace std;

int main()
{
	char src[MAX],des[MAX];
	int dp=0,slen;
	vector<char> ans;

	scanf("%s",src);
	scanf("%s",des);

	for(int i=0;i<strlen(src);i++)
		src[i] = toupper(src[i]);

	for(int i=0;i<strlen(des);i++)
		des[i] = toupper(des[i]);

	slen = strlen(src);
	for(int i=0;i<slen;i++){
		if(src[i] != des[dp]){
			int j;
			for(j=0;j<ans.size();j++){
				if(src[i] == ans[j])
					break;
			}
			if(j == ans.size())
				ans.push_back(src[i]);
		}
		else{
			dp++;
		}
	}

	for(int i=0;i<ans.size();i++){
		printf("%c",ans[i]);
	}

	return 0;
}