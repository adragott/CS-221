#ifndef _TESTDRIVER_H_
#define _TESTDRIVER_H_

#pragma once
#include "TreeType.h"
class TestDriver
{
public:
	TestDriver();
	~TestDriver();

	int Populate(const char* input, TreeType &treeUsers) const;
	void Test(std::ofstream& outFile, TreeType& treeUsers) const;
private:

};


#endif