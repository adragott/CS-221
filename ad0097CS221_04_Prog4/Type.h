// Type.h -- contains all type structures relevant to this assignment, except for TreeType because it is actually useful

#ifndef _TYPE_H_
#define _TYPE_H_
#pragma once

enum RelationType 
{ 
	LESS, 
	EQUAL, 
	GREATER 
};

class DateType
{
public:
	DateType();
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

class ItemType
{
public:
	ItemType();
	~ItemType();
	void Print() const;
	int GetValue() const;
	void SetValue(int val);
	RelationType ComparedTo(ItemType ot);
private:
	int value;
};

#endif