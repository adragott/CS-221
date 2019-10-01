#include "DateType.h"


DateType::DateType(int newMonth, int newDay, int newYear) : month(newMonth), day(newDay), year(newYear) {}
DateType::~DateType() {}

void DateType::Initialize(int newMonth, int newDay, int newYear)
{
	year = newYear;
	month = newMonth;
	day = newDay;
}

int DateType::GetMonth() const
{
	return month;
}

int DateType::GetYear() const
{
	return year;
}

int DateType::GetDay() const
{
	return day;
}

RelationType DateType::ComparedTo(DateType aDate)
{
	if (year < aDate.year)
	{
		return LESS;
	}
	else if (year > aDate.year)
	{
		return GREATER;
	}
	else if (month < aDate.month)
	{
		return LESS;
	}
	else if (month > aDate.month)
	{
		return GREATER;
	}
	else if (day < aDate.day)
	{
		return LESS;
	}
	else if (day > aDate.day)
	{
		return GREATER;
	}
	else
	{
		return EQUAL;
	}
}
