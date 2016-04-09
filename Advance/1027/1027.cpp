#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

char getDigit(int y)
{
	if(y < 10)
		return '0'+y;
	else
		return 'A'+(y-10);
}

string getNum(int x)
{
	string str = "00";
	if(x < 13)
		str[1] = getDigit(x);
	else{
		str[0] = getDigit(x/13);
		str[1] = getDigit(x%13);
	}

	return str;
}

int main()
{
	int r,g,b;
	cin >> r >> g >> b;
	cout << '#' << getNum(r) << getNum(g) << getNum(b);

	return 0;
}