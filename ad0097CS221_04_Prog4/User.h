#ifndef _USER_H_
#define _USER_H_

#pragma once
#include "homework.h"
#include "DateType.h"
#include <fstream>
#define STR_STREET_LEN		30
#define STR_CITY_LEN		30
#define STR_FNAME_LEN		30
#define STR_LNAME_LEN		30
#define STR_EMAIL_LEN		30
#define STR_MAJOR_LEN		20
#define STR_STATE_LEN		3

// Bit positions for privacy codes
//enum PRIVACY_CODE_Pos
//{
//	FNAME_bp =			0x0,
//	LNAME_bp =			0x1,
//	GENDER_bp =			0x2,
//	MAJOR_bp =			0x3,
//	STREET_INFO_bp =	0x4,
//	CITY_bp =			0x5,
//	ZIP_bp =			0x6,
//	STATE_bp =			0x7,
//	GPA_bp =			0x8,
//	MONTH_DOB_bp =		0x9,
//	DAY_DOB_bp =		0x0A,
//	YEAR_DOB_bp =		0x0B,
//	EMAIL_bp =			0x0C
//};
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
	FNAME_bm =			(1 << FNAME_bp),
	LNAME_bm =			(1 << LNAME_bp),
	GENDER_bm =			(1 << GENDER_bp),
	MAJOR_bm =			(1 << MAJOR_bp),
	STREET_INFO_bm =	(1 << STREET_INFO_bp),
	CITY_bm =			(1 << CITY_bp),
	ZIP_bm =			(1 << ZIP_bp),
	STATE_bm =			(1 << STATE_bp),
	GPA_bm =			(1 << GPA_bp),
	MONTH_DOB_bm =		(1 << MONTH_DOB_bp),
	DAY_DOB_bm =		(1 << DAY_DOB_bp),
	YEAR_DOB_bm =		(1 << YEAR_DOB_bp),
	EMAIL_bm =			(1 << EMAIL_bp),
};


struct AddressType
{
public:
	AddressType();
	AddressType(const char* argStreetName, const char* argCity, const char* argState, int argStreetNo, int argZip);
	char streetName[STR_STREET_LEN + 1];
	char city[STR_CITY_LEN + 1];
	char state[STR_STATE_LEN + 1];
	int streetNo;
	int zip;
};

class User
{
public:
	User();
	User(const char* argFname, const char* argLname, char argGender, const char* argMajor, AddressType argAddress, 
		float argGPA, DateType argDateOfBirth, const char* argEmail, int argpCode);
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
	void GetDateOfBirth(DateType &aDateOfBirth, int code = 0) const;
	//for private GPA, return -1.0 if incorrect code is provided
	float GetGPA(int code = 0) const;
	//for private GPA, set aGPA to - 1.0 if incorrect code is provided
	void GetGPA(float& aGPA, int code = 0) const;
	//for private address fields, for string fields return “------“, for integer fields to 0 if incorrect code is provided
	AddressType GetAddress(int code = 0) const;
	//for private address fields, return “------“ for string fields and 0 for integer fields to 0 if incorrect code is provided
	void GetAddress(AddressType &aAddress, int code = 0) const;

	void GetAddress(char aStreetName[], int& aStreetNo, char aCity[], int& aZip, char aState[], int code = 0) const;

	void SetFirstName(const char* afName);
	void SetLastName(const char* alName);
	void SetMajor(const char* amajor);
	void SetEmail(const char* anemail);
	void SetGender(char aGender);
	void SetDateOfBirth(DateType aDateOfBirth);
	void SetGPA(float aGPA);
	void SetAddress(AddressType aAddress);
	void SetAddress(char aStreetName[], int aStreetNo, char aCity[], int aZip, char aState[]);
	void SetPrivacycode(int code);

	void Display(int code = 0) const;
	void Display(std::ofstream &outFile, int code = 0) const;

	void Implementer(char name[]) const;
private:
	// First name of user
	char fname[STR_FNAME_LEN + 1];
	// Last name of user
	char lname[STR_LNAME_LEN + 1];
	// Major of user
	char major[STR_MAJOR_LEN + 1];
	// Email of user
	char email[STR_EMAIL_LEN + 1];
	// Gender of user
	char gender;
	// Privacy code for user -- used to indicate accessibility of user's information
	int privacyCode;
	// GPA of user
	float gpa;
	// Address of user
	AddressType address;
	// Date of birth of user
	DateType dateOfBirth;
	// Function that allows me to put the guts of my code here so the user can call one of the two public variants
	// and I can call this
	void LocalDisplay(std::ostream &outStream, int code = 0) const;
};

#endif