// 所有的字段都是用字符串，来得方便直接
// 如果在scanf或者cin后面要使用getline或者gets，先用gets或者getline吃个空格

#include <cstring>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

#define MAX 85
#define NUMBER 10

using namespace std;

struct book {
	char id[NUMBER];
	char title[MAX];
	char author[MAX];
	char keywords[MAX];
	char pub[MAX];
	char year[NUMBER];
};

bool cmp(struct book a,struct book b){
	return strcmp(a.id,b.id)<0;
}

int main()
{
	vector<struct book> books;
	int n,m;
	char blank[MAX];


	scanf("%d",&n);
	gets(blank);
	for(int i=0;i<n;i++){
		struct book tbook;
		gets(tbook.id);
		gets(tbook.title);
		gets(tbook.author);
		gets(tbook.keywords);
		gets(tbook.pub);
		gets(tbook.year);
		books.push_back(tbook);
	}

	sort(books.begin(),books.end(),cmp);

	scanf("%d",&m);
	gets(blank);
	for(int i=0;i<m;i++){
		char query[100],type,cont[MAX];
		gets(query);
		printf("%s\n",query);
		type = query[0];
		strcpy(cont,query+3);

		bool found = false;

		if(type == '1'){
			for(int j=0;j<n;j++){
				if(!strcmp(books[j].title,cont)){
					printf("%s\n",books[j].id);
					found = true;
				}
			}
		}
		else if(type == '2'){
			for(int j=0;j<n;j++){
				if(!strcmp(books[j].author,cont)){
					printf("%s\n",books[j].id);
					found = true;
				}
			}
		}
		else if(type == '3'){
			for(int j=0;j<n;j++){
				if(strstr(books[j].keywords,cont) != NULL){
					printf("%s\n",books[j].id);
					found = true;
				}
			}
		}
		else if(type == '4'){
			for(int j=0;j<n;j++){
				if(!strcmp(books[j].pub,cont)){
					printf("%s\n",books[j].id);
					found = true;
				}
			}
		}
		else if(type == '5'){
			for(int j=0;j<n;j++){
				if(!strcmp(books[j].year,cont)){
					printf("%s\n",books[j].id);
					found = true;
				}
			}
		}

		if(!found)
			printf("Not Found\n");
	}

	return 0;
}