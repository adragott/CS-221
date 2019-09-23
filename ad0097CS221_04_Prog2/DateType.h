#ifndef _DATETYPE_H_
#define _DATETYPE_H_

#include "homework.h"

enum RelationType {LESS, EQUAL, GREATER};

class DateType
{
public:
	DateType(int newMonth, int newDay, int newYear);
	~DateType();
	void Initialize(int newMonth, int newDay, int newYear);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

	RelationType ComparedTo(DateType aDate);
private:
	int year;
	int month;
	int day;
};

#endif