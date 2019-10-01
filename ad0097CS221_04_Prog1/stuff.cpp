#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;

class stuff
{
public:
	stuff()
	{
		memset(_x, '\0', 30);
	}
	stuff(const char* x) : _x()
	{
		memcpy(_x, x, 30);
	}
	~stuff(){}
	
	void printStuff();
private:
	char _x[30];
};



int main()
{
	stuff stuffers();
	stuffers.printStuff();
	return 0;
}

void stuff::printStuff()
{
	cout << string(_x) << endl;
}