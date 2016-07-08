#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

// reg_num使用long long，在输出的时候注意格式化为13位

struct Testee {
	unsigned long long reg_num;
	unsigned int loc_num;
	unsigned int local_rank;
	unsigned int total_rank;
	int score;
};


vector<vector<struct Testee> > testees;
vector<struct Testee> final_testees;

bool sortByScore(const struct Testee t1, const struct Testee t2)
{
	if (t1.score == t2.score)
		return t1.reg_num < t2.reg_num;
	return t1.score >  t2.score;
}

int main()
{
	unsigned int locs;
	unsigned int testee_num;

	scanf("%u",&locs);
	for(int i=1;i<=locs;i++)
	{
		vector<struct Testee> loc_testees;
		scanf("%u",&testee_num);
		for(int j=1;j<=testee_num;j++)
		{
			struct Testee testee;
			scanf("%llu %u",&testee.reg_num, &testee.score);
			testee.loc_num = i;
			// insert 居然是复制，而不是引用
			loc_testees.insert(loc_testees.end(), testee);
			
		}
		sort(loc_testees.begin(), loc_testees.end(), sortByScore);
		testees.insert(testees.end(), loc_testees);
	}

	int positions[locs] = {0};

	while(true)
	{
		int max_score=-1;
		int max_loc=-1;

		for(int i=0;i<locs;i++)
		{
			if(positions[i] < testees[i].size())
			{
				struct Testee &temp = testees[i][positions[i]];
				if(positions[i] > 0 && temp.score == testees[i][positions[i]-1].score)
					temp.local_rank = testees[i][positions[i]-1].local_rank;
				else
					temp.local_rank = positions[i]+1;

				if(temp.score > max_score || (temp.score == max_score && temp.reg_num < testees[max_loc][positions[max_loc]].reg_num))
				{
					max_score = temp.score;
					max_loc = i;
				}
			}				
		}
		
		if(max_score == -1)
			break;
		
		final_testees.insert(final_testees.end(),testees[max_loc][positions[max_loc]]);
		positions[max_loc]++;
	}

	printf("%zu\n", final_testees.size());
	final_testees[0].total_rank = 1;
	printf("%013llu %u %u %u",final_testees[0].reg_num,1,final_testees[0].loc_num, final_testees[0].local_rank);
	for(size_t i=1;i<final_testees.size();i++)
	{
		// 设置rank，然后输出
		if (final_testees[i].score == final_testees[i-1].score)	
			final_testees[i].total_rank = final_testees[i-1].total_rank;
		else
			final_testees[i].total_rank = i+1;

		printf("\n%013llu %u %u %u",final_testees[i].reg_num, final_testees[i].total_rank, final_testees[i].loc_num, final_testees[i].local_rank);
	}
	
	return 0;
		
}
