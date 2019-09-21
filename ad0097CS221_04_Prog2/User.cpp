#include "User.h"
#include <cstring>
// AddressType Definitions
AddressType::AddressType()
{

}
c
AddressType::AddressType(const char* argStreetName, const char* argCity, const char* argState, int argStreetNo, int argZip)
	: streetNo(argStreetNo), zip(argZip)
{
	memset(streetName, '\0', 
	strcpy(streetName, argStreetName);
}

// User Definition
User::User()
{

}

User::User(const char* argFname, const char* argLname, char argGender, const char* argMajor, AddressType argAddress, float argGPA, DateType argDateOfBirth, char* argEmail, int argpCode) : 
	fname(), lname(), gender('0'), major(), address(argAddress), gpa(argGPA), dateOfBirth(argDateOfBirth), email(), privacyCode((uint16_t)argpCode)
{
	strcpy(fname, argFname);
	strcpy(lname, argLname);

	strcpy(major, argMajor);
	strcpy(email, argEmail);
	//// memcpy, memset not safe in non-POD types
	//// so I am setting this cstrings manually
	//// after each string copy is done, i check to make sure the index hasn't reached it's limit. 
	//// If it has, the string is broken
	//int ind = 0;
	//// set first name
	//for (const char* _tempStr = argFname; (*_tempStr && (ind < STR_FNAME_LEN)); *_tempStr++)
	//{
	//	fname[ind++] = *_tempStr;
	//}
	//ind = 0;
	//// set last name
	//for (const char* _tempStr = argLname; (*_tempStr && (ind < STR_LNAME_LEN)); *_tempStr++)
	//{
	//	lname[ind++] = *_tempStr;
	//}
	//
	//ind = 0;
	//// set major
	//for (const char* _tempStr = argMajor; (*_tempStr && *(ind < STR_MAJOR_LEN)); *_tempStr++)
	//{
	//	major[ind++] = *_tempStr;
	//}

	//ind = 0;
	//// set email
	//for (const char* _tempStr = argEmail; (*_tempStr && (ind < STR_EMAIL_LEN)); *_tempStr++)
	//{
	//	email[ind++] = *_tempStr;
	//}

	std::cout << fname << std::endl;
	std::cout << lname << std::endl;
	std::cout << major << std::endl;
}

User::~User()
{

}

void User::GetFirstName(char afname[], int code) const
{
}

void User::GetLastName(char alname[], int code) const
{
}

void User::GetMajor(char amajor[], int code) const
{
}

void User::GetEmail(char anemail[], int code) const
{
}

void User::GetGender(char& agender, int code) const
{
}

DateType User::GetDateOfBirth(int code) const
{
	return DateType();
}

void User::GetDateOfBirth(DateType& aDateOfBirth, int code) const
{
}

float User::GetGPA(int code) const
{
	return 0.0f;
}

void User::GetGPA(float& aGPA, int code) const
{
}

AddressType User::GetAddress(int code) const
{
	return AddressType();
}

void User::GetAddress(AddressType& aAddress, int code) const
{
}

void User::GetAddress(char aStreetName[], int& aStreetNo, char aCity[], int& aZip, char aState[], int code) const
{
}
