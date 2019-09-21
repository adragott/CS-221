/*
Author:				Anthony Dragotta
Username:			ad0097
Assignment Number:	2

 -- User.hpp --


 -- !User.hpp --
*/

#ifndef _USER_H_
#define _USER_H_

#pragma once
#include "homework.h"
#include "DateType.h"

#define STR_STREET_LEN		30
#define STR_CITY_LEN		30
#define STR_FNAME_LEN		30
#define STR_LNAME_LEN		30
#define STR_EMAIL_LEN		30
#define STR_MAJOR_LEN		5
#define STR_STATE_LEN		3

static const int ACCESS_CODE = 8213479;

enum PRIVACY_CODE
{
	PC_FNAME =			0x0,
	PC_LNAME =			0x1,
	PC_GENDER =			0x2,
	PC_MAJOR =			0x3,
	PC_STREET_INFO =	0x4,
	PC_CITY =			0x5,
	PC_ZIP =			0x6,
	PC_STATE =			0x7,
	PC_GPA =			0x8,
	PC_MONTH_DOB =		0x9,
	PC_DAY_DOB =		0x0A,
	PC_YEAR_DOB =		0x0B,
	PC_EMAIL =			0x0C
};

struct AddressType
{
public:
	AddressType();
	AddressType(const char* argStreetName, const char* argCity, const char* argState, int argStreetNo, int argZip);
	char streetName[STR_STREET_LEN];
	char city[STR_CITY_LEN];
	char state[STR_STATE_LEN];
	int streetNo;
	int zip;
};

class User
{
public:
	User();
	User(const char* argFname, const char* argLname, char argGender, const char* argMajor, AddressType argAddress, 
		float argGPA, class DateType argDateOfBirth, char* argEmail, int argpCode);
	~User();
	//for private fname, afname will be set to “------“ if incorrect code is provided
	void GetFirstName(char afname[], int code = 0) const;
	//for private lname, alname will be set to “------“ if incorrect code is provided
	void GetLastName(char alname[], int code = 0) const;
	
	//for private major, amajor will be set to “------“ if incorrect code is provided
	void GetMajor(char amajor[], int code = 0) const;
	
	//for private email, anemail will be set to “------@----- - “if incorrect code is provided
	void GetEmail(char anemail[], int code = 0) const;
	
	//for private gender will be set to “ & “if incorrect code is provided
	void GetGender(char& agender, int code = 0) const;
	
	//for private DOB, set the corresponding field to 0 if incorrect code is provided
	DateType GetDateOfBirth(int code = 0) const;
	
	//for private DOB, set the corresponding field to 0 if incorrect code is provided
	void GetDateOfBirth(DateType & aDateOfBirth, int code = 0) const;
	
	//for private GPA, return -1.0 if incorrect code is provided
	float GetGPA(int code = 0) const;
	
	//for private GPA, set aGPA to - 1.0 if incorrect code is provided
	void GetGPA(float& aGPA, int code = 0) const;
	
	//for private address fields, for string fields return “------“, for integer fields to 0 if incorrect code is provided
	AddressType GetAddress(int code = 0) const;
	
	//for private address fields, return “------“ for string fields and 0 for integer fields to 0 if incorrect code is provided
	void GetAddress(AddressType & aAddress, int code = 0) const;
	
	void GetAddress(char aStreetName[], int& aStreetNo, char aCity[], int& aZip, char aState[], int code = 0) const;
private:
	char fname[STR_FNAME_LEN];
	char lname[STR_LNAME_LEN];
	char major[STR_MAJOR_LEN];
	char gender;
	AddressType address;
	float gpa;
	DateType dateOfBirth;
	char email[STR_EMAIL_LEN];
	uint16_t privacyCode;
};

#endif