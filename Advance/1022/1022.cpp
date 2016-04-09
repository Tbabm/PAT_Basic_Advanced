// 第一遍过两个点
// 第二遍改成%07d继续过两个点!!!(注意格式化)
// 第三遍加了default，然而并没有什么用

// 注意如何手写split
// 注意string.find用法
// 注意map的常见用法
// sort的用法

// 参考：
// 1. http://blog.csdn.net/chen895281773/article/details/8630141
// 2. http://blog.csdn.net/wyxdexyq/article/details/40559469

// 测试点1仍然过不了，猜测是split的过程出问题了
// 总结1中的split方法
// 总结2中的C语言做法


#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>

#define ANOTHER_SPLIT 1

#define MAX_BOOKS 10005

using namespace std;

struct book {
	unsigned int id;
	string title;
	string author;
	vector<string> keywords;
	string publisher;
	unsigned int year;
} books[MAX_BOOKS];

map< string,vector<unsigned int> > keys;

int n,m;

void split(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1,pos2;
	pos2 = s.find(c);
	pos1 = 0;

	while(pos2 != string::npos){
		v.push_back(s.substr(pos1,pos2-pos1));
		pos1 = pos2+c.length();
		pos2 = s.find(c,pos1);	//第二次从pos1开始找起
	}

	if(pos1 != s.length())
		v.push_back(s.substr(pos1));
}

bool cmp(struct book a,struct book b){
	return a.id < b.id;
}

void searchTitle(const string& title){
	cout << "1: "<< title << endl;
	bool found = false;
	for(int i=0;i<n;i++){
		if(books[i].title == title){
			printf("%07d\n",books[i].id);
			found = true;
		}
	}
	if(!found)
		cout << "Not Found"<<endl;
}

void searchAuthor(const string& author){
	cout << "2: "<< author << endl;
	bool found = false;
	for(int i=0;i<n;i++){
		if(books[i].author == author){
			printf("%07d\n",books[i].id);
			found = true;
		}
	}
	if(!found)
		cout << "Not Found" << endl;
}

void searchKey(const string& key){
	cout << "3: "<< key << endl;
	// 如果一本书有两个一样的关键词，那么这种方案会打印出两个
	// if(keys.find(key) == keys.end())
	// 	cout << "Not Found" << endl;
	// else{
	// 	sort(keys[key].begin(),keys[key].end());
	// 	for(int i=0;i<keys[key].size();i++){
	// 		printf("%07d\n",keys[key][i]);
	// 	}
	// }

	bool found= false;
	for(int i=0;i<n;i++){
		for(int j=0;j<books[i].keywords.size();j++){
			if(books[i].keywords[j] == key){
				found = true;
				printf("%07d\n",books[i].id);
				break;
			}
		}
	}
	if(!found)
		cout << "Not Found" << endl;
}

void searchPub(const string& pub){
	cout << "4: "<< pub << endl;
	bool found = false;
	for(int i=0;i<n;i++){
		if(books[i].publisher == pub){
			printf("%07d\n",books[i].id);
			found = true;
		}
	}
	if(!found)
		cout << "Not Found" << endl;
}

void searchYear(const unsigned int year){
	cout << "5: "<< year << endl;
	bool found = false;
	for(int i=0;i<n;i++){
		if(books[i].year == year){
			printf("%07d\n",books[i].id);
			found = true;
		}
	}
	if(!found)
		cout << "Not Found" << endl;
}

int main()
{	
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		string temp;
		cin >> books[i].id;
		cin.get();	// cin和getline之间要吃一个回车
		getline(cin, books[i].title);
		getline(cin, books[i].author);
		getline(cin, temp);
		#ifdef ANOTHER_SPLIT
			istringstream is(temp);
			string tmp;
			while(is>>tmp)
				books[i].keywords.push_back(tmp);
		#else
			split(temp,books[i].keywords," ");		
			for(int j=0;j<books[i].keywords.size();j++){
				if(keys.find(books[i].keywords[j]) == keys.end()){
					vector<unsigned int> temp;
					temp.push_back(books[i].id);
					keys[books[i].keywords[j]] = temp;	// 这里是复制了一份temp
				}
				else
					keys[books[i].keywords[j]].push_back(books[i].id);
			}
		#endif
		getline(cin, books[i].publisher);
		cin >> books[i].year;
	}

	sort(books,books+n,cmp);

	scanf("%d",&m);
	getchar();	// 加上也没用
	for(int i=0;i<m;i++){
		int type;
		unsigned int year;
		string cont;
		cin >> type;
		if(type == 5){
			cin >> cont;
			cin >> year;
		}
		else{
			getline(cin,cont);
			cont = cont.substr(2);
		}
		switch(type){
			case 1:
				searchTitle(cont);
				break;
			case 2:
				searchAuthor(cont);
				break;
			case 3:
				searchKey(cont);
				break;
			case 4:
				searchPub(cont);
				break;
			case 5:
				searchYear(year);
				break;
			default:
				cout << "Not Found" << endl;
		}
	}

	return 0;
}