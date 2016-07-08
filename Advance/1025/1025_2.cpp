#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

// 使用string，cin和cout之后，多出了近两倍的时间

typedef struct Stu {
	string id;
	unsigned int loc, locRank, rank;
	int score;
	
	bool operator > (const struct Stu& b) const
	{
		if (score == b.score)
			return id < b.id;
		else
			return score > b.score;
	}
} Student;

vector<vector<Student> > all;
vector<Student> fin;

int main()
{
	unsigned int locNum;
	cin >> locNum;

	for (int i=0; i<locNum ; i++)
	{
		unsigned int num;
		cin >> num;	

		vector<Student> curStus(num);
		for (int j=0; j<num ; j++)
		{
			cin >> curStus[j].id >> curStus[j].score;
			curStus[j].loc = i+1;
		}
		
		sort(curStus.begin(), curStus.end(), greater<Student>());
		all.push_back(curStus); 	
	}

	int pos[locNum] = {0};
	while(true)
	{
		int max_score = -1;
		int max_loc = -1;
		
		for (int i=0 ; i<locNum; i++)
		{
			if (pos[i] < all[i].size())
			{
				int p = pos[i];	
				Student &temp = all[i][p];
				// 确定组内排名
				if (p > 0 && (temp.score == all[i][p-1].score))
					temp.locRank = all[i][p-1].locRank;
				else
					temp.locRank = p+1;
				
				// 更新max
				if (temp.score > max_score || (temp.score == max_score && temp.id < all[max_loc][pos[max_loc]].id) )
				{
					max_score = temp.score;
					max_loc = i;
				}
			}
					
		}

		if (max_score == -1)
			break;
		
		fin.push_back(all[max_loc][pos[max_loc]]);
		pos[max_loc]++;
	}

	fin[0].rank = 1;
	printf("%zu\n", fin.size());
	cout << fin[0].id;
	printf(" %u %u %u", fin[0].rank, fin[0].loc, fin[0].locRank);
	//cout << fin.size() << endl;
	//cout << fin[0].id << " " << 1 << " " << fin[0].loc << " " << fin[0].locRank;
	for (size_t i=1; i<fin.size(); i++)
	{
		if (fin[i].score == fin[i-1].score)
			fin[i].rank = fin[i-1].rank;
		else
			fin[i].rank = i+1;
		
		cout << endl << fin[i].id;
		printf(" %u %u %u", fin[i].rank, fin[i].loc, fin[i].locRank);
		//cout << endl;
		//cout << fin[i].id << " " <<  fin[i].rank << " " <<  fin[i].loc << " " <<  fin[i].locRank;
	}

	return 0;
}
