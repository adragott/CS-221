#include "Type.h"
#include <cstring>

DateType::DateType() : month(0), day(0), year(0) {}
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

// AddressType Definitions
AddressType::AddressType() :
	streetNo(-1), zip(-1)
{
	memset(streetName, '\0', USER_STR_STREET_LEN + 1);
	memset(city, '\0', USER_STR_CITY_LEN + 1);
	memset(state, '\0', USER_STR_STATE_LEN + 1);
}

AddressType::AddressType(const char* argStreetName, const char* argCity, const char* argState, int argStreetNo, int argZip)
	: streetNo(argStreetNo), zip(argZip)
{
	strcpy(streetName, argStreetName);
	strcpy(city, argCity);
	strcpy(state, argState);
}
