#ifndef _DATETYPE_H_
#define _DATETYPE_H_

#include "homework.h"

class DateType
{
public:
	DateType();
	DateType(int argDay, int argMonth, int argYear);
	~DateType();
private:
	int day;
	int month;
	int year;
};

#endif