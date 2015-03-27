#include <iostream>
#include <cstring>

using namespace std;

#define MAX 82

int main(){
	char input[MAX];
	int n1, n2,len;

	cin >> input;
	len = strlen(input);
	n1 = (len+2)/3;
	n2 = (len + 2) - 2 * n1;
	
	for (int i = 0; i < n1-1; i++){
		printf("%c", input[i]);
		for (int j = 0; j < n2 - 2; j++)
			printf(" ");
		printf("%c\n", input[len - i-1]);
	}
	for (int i = 0; i < n2; i++){
		printf("%c", input[n1 - 1 + i]);
	}
	printf("\n");

	return 0;
}