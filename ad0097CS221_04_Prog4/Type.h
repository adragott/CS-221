// Type.h -- contains all type structures relevant to this assignment, except for TreeType because it is actually useful

#ifndef _TYPE_H_
#define _TYPE_H_
#pragma once
#include "homework.h"

#define USER_STR_STREET_LEN		30
#define USER_STR_CITY_LEN		30
#define USER_STR_FNAME_LEN		30
#define USER_STR_LNAME_LEN		30
#define USER_STR_EMAIL_LEN		30
#define USER_STR_MAJOR_LEN		20
#define USER_STR_STATE_LEN		3

enum RelationType 
{ 
	LESS, 
	EQUAL, 
	GREATER 
};

enum PRIVACY_CODE_Pos
{
	EMAIL_bp = 0x0,
	YEAR_DOB_bp = 0x1,
	DAY_DOB_bp = 0x2,
	MONTH_DOB_bp = 0x3,
	GPA_bp = 0x4,
	STATE_bp = 0x5,
	ZIP_bp = 0x6,
	CITY_bp = 0x7,
	STREET_INFO_bp = 0x8,
	MAJOR_bp = 0x9,
	GENDER_bp = 0x0A,
	LNAME_bp = 0x0B,
	FNAME_bp = 0x0C
};

// Bit masks for privacy codes
enum PRIVACY_CODE_Mask
{
	FNAME_bm = (1 << FNAME_bp),
	LNAME_bm = (1 << LNAME_bp),
	GENDER_bm = (1 << GENDER_bp),
	MAJOR_bm = (1 << MAJOR_bp),
	STREET_INFO_bm = (1 << STREET_INFO_bp),
	CITY_bm = (1 << CITY_bp),
	ZIP_bm = (1 << ZIP_bp),
	STATE_bm = (1 << STATE_bp),
	GPA_bm = (1 << GPA_bp),
	MONTH_DOB_bm = (1 << MONTH_DOB_bp),
	DAY_DOB_bm = (1 << DAY_DOB_bp),
	YEAR_DOB_bm = (1 << YEAR_DOB_bp),
	EMAIL_bm = (1 << EMAIL_bp),
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


struct AddressType
{
public:
	AddressType();
	AddressType(const char* argStreetName, const char* argCity, const char* argState, int argStreetNo, int argZip);
	char streetName[USER_STR_STREET_LEN + 1];
	char city[USER_STR_CITY_LEN + 1];
	char state[USER_STR_STATE_LEN + 1];
	int streetNo;
	int zip;
};


#endif