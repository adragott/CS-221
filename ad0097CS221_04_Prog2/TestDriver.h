#ifndef _TESTDRIVER_H_
#define _TESTDRIVER_H_

#include "homework.h"



// forward declaration for User class
class User;


class TestDriver
{
public:
	TestDriver();
	~TestDriver();

	int Populate(const char* input, User users[]);
	void Test(User users[], int count);
	void Test(std::ofstream& outFile, User users[], int count);
};

#endif