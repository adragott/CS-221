#include "User.h"
#include <cstring>
#include <string>
#include <iomanip>
// AddressType Definitions
AddressType::AddressType() : 
	streetNo(-1), zip(-1)
{
	memset(streetName, '\0', STR_STREET_LEN);
	memset(city, '\0', STR_CITY_LEN);
	memset(state, '\0', STR_STATE_LEN);
}

AddressType::AddressType(const char* argStreetName, const char* argCity, const char* argState, int argStreetNo, int argZip)
	: streetNo(argStreetNo), zip(argZip)
{
	strcpy(streetName, argStreetName);
	strcpy(city, argCity);
	strcpy(state, argState);
}


User::User() : 
	gender('0'), address(), gpa(-1.f), dateOfBirth(0, 0, 0), privacyCode((uint16_t)0)
{
	memset(fname, '\0', STR_FNAME_LEN);
	memset(lname, '\0', STR_LNAME_LEN);
	memset(major, '\0', STR_MAJOR_LEN);
	memset(email, '\0', STR_EMAIL_LEN);
}

User::User(const char* argFname, const char* argLname, char argGender, const char* argMajor, AddressType argAddress, float argGPA, DateType argDateOfBirth, const char* argEmail, int argpCode) : 
	fname(), lname(), gender(argGender), address(argAddress), major(), gpa(argGPA), dateOfBirth(argDateOfBirth), email(), privacyCode((uint16_t)argpCode)
{
	strcpy(fname, argFname);
	strcpy(lname, argLname);
	strcpy(major, argMajor);
	strcpy(email, argEmail);
}

User::~User() {}

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
	// check if gpa requires access (aka locked)
	if (privacyCode & GPA_bm)
	{
		// check if the code provided is the code we require for access
		if (privacyCode == code)
		{
			// the code matched so return the users gpa
			return gpa;
		}
		else
		{
			return -1.0f;
		}
	}
	// if its not locked, we can give the value
	else
	{
		return gpa;
	}
}

void User::GetGPA(float& aGPA, int code) const
{
	aGPA = GetGPA(code);
}

AddressType User::GetAddress(int code) const
{
	return AddressType();
}

void User::GetAddress(AddressType& aAddress, int code) const
{
	GetAddress(aAddress.streetName, aAddress.streetNo, aAddress.city, aAddress.zip, aAddress.state, code);
}

void User::GetAddress(char aStreetName[], int& aStreetNo, char aCity[], int& aZip, char aState[], int code) const
{
	// Street Info (Street Number and Street Name)
	// check if street info requires access (aka locked)
	if (privacyCode & STREET_INFO_bm)
	{
		// it requires access so now check if the code provided is equal to our privacy code
		if (privacyCode == code)
		{
			// the codes match so we assign the real values
			strcpy(aStreetName, address.streetName);
			aStreetNo = address.streetNo;
		}
		else
		{
			// codes didn't match so we assign bad values to indicate a bad code
			memset(aStreetName, '\0', STR_STREET_LEN);
			memset(aStreetName, '-', 5);
			aStreetNo = 0;
		}
	}
	else
	{
		// don't require a code so we assign the real values
		strcpy(aStreetName, address.streetName);
		aStreetNo = address.streetNo;
	}

	// City
	// check if city requires access (aka locked)
	if (privacyCode & CITY_bm)
	{
		// it requires access so now check if the code provided is equal to our privacy code
		if (privacyCode == code)
		{
			// the codes match so we assign the city its value
			strcpy(aCity, address.city);
		}
		else
		{
			// bad access code so we assign a bad city to indicate a bad code
			memset(aCity, '\0', STR_CITY_LEN);
			memset(aCity, '-', 5);
		}
	}
	else
	{
		// don't require a code so we assign the actual city
		strcpy(aCity, address.city);
	}

	// Zip
	// check if zip requires access code (aka locked)
	if (privacyCode & ZIP_bm)
	{
		// it requires access so now check if the code provided is equal to our privacy code
		if (privacyCode == code)
		{
			// the codes match so we assign the real zip code
			aZip = address.zip;
		}
		else
		{

		}
	}
	else
	{
		// don't require a code so we assign the actual city
		aZip = address.zip;
	}

}

void User::Display(int code) const
{
	std::cout << "First name: " << fname << std::endl;
	std::cout << "Last name: " << lname << std::endl;
	std::cout << "Gender: " << gender << std::endl;
	std::cout << "Major: " << major << std::endl;
	std::cout << "Street Info: " << address.streetNo << " " << address.streetName << std::endl;
	std::cout << "City: " << address.city << std::endl;
	std::cout << "State: " << address.state << std::endl;
	std::cout << "ZIP: " << address.zip << std::endl << std::endl;
	std::cout << "GPA: " << std::fixed << std::setprecision(2) << gpa << std::endl;
	std::cout << "Date of birth: " << std::setw(2) << std::setfill('0') << dateOfBirth.GetMonth() << "/" << dateOfBirth.GetDay() << "/" <<
		std::setw(4) << dateOfBirth.GetYear() << std::endl;
	std::cout << "Email: " << email << std::endl;
	std::cout << "Privacy Code: " << privacyCode << std::endl;
	std::cout << std::endl;
}