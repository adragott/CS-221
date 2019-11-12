#ifndef _TESTDRIVER_H_
#define _TESTDRIVER_H_

#pragma once
#include "homework.h"
#include "TreeType.h"
class TestDriver
{
public:
	TestDriver();
	~TestDriver();

	int Populate(const char* input, TreeType &treeUsers) const;
	void Test(std::ofstream& outFile, TreeType& treeUsers) const;
	void Test(const char* input_file_name, TreeType& treeUsers) const;
private:

};


#endif