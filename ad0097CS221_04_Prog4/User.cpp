#include "User.h"
#include <cstring>
#include <string>
#include <iomanip>
#include <fstream>



User::User() : 
	gender('0'), address(), gpa(-1.f), dateOfBirth(0, 0, 0), privacyCode(0)
{
	memset(fname, '\0', USER_STR_FNAME_LEN + 1);
	memset(lname, '\0', USER_STR_LNAME_LEN + 1);
	memset(major, '\0', USER_STR_MAJOR_LEN + 1);
	memset(email, '\0', USER_STR_EMAIL_LEN + 1);
}

User::User(const char* argFname, const char* argLname, char argGender, const char* argMajor, AddressType argAddress, float argGPA, DateType argDateOfBirth, const char* argEmail, int argpCode) : 
	fname(), lname(), gender(argGender), address(argAddress), major(), gpa(argGPA), dateOfBirth(argDateOfBirth), email(), privacyCode(argpCode)
{
	strcpy(fname, argFname);
	strcpy(lname, argLname);
	strcpy(major, argMajor);
	strcpy(email, argEmail);
}

User::~User() {}

bool User::operator<(User* user)
{
	// arrays to hold other users' strings
	char other_user_fname[USER_STR_FNAME_LEN + 1];
	char other_user_lname[USER_STR_LNAME_LEN + 1];

	//null them out for safety
	memset(other_user_fname, '\0', USER_STR_FNAME_LEN + 1);
	memset(other_user_lname, '\0', USER_STR_LNAME_LEN + 1);
	
	// get other users first and last name
	user->GetFirstName(other_user_fname);
	user->GetLastName(other_user_lname);

	// std::string versions for easy comparison
	std::string s_lname(lname);
	std::string s_fname(fname);
	std::string s_olname(other_user_lname);
	std::string s_ofname(other_user_fname);

	if((s_lname < s_olname) && (s_fname < s_ofname))
	{
		return true;
	}
	return false;
}

bool User::operator>(User* user)
{
	// arrays to hold other users' strings
	char other_user_fname[USER_STR_FNAME_LEN + 1];
	char other_user_lname[USER_STR_LNAME_LEN + 1];

	//null them out for safety
	memset(other_user_fname, '\0', USER_STR_FNAME_LEN + 1);
	memset(other_user_lname, '\0', USER_STR_LNAME_LEN + 1);
	
	// get other users first and last name
	user->GetFirstName(other_user_fname);
	user->GetLastName(other_user_lname);

	// std::string versions for easy comparison
	std::string s_lname(lname);
	std::string s_fname(fname);
	std::string s_olname(other_user_lname);
	std::string s_ofname(other_user_fname);

	if((s_lname > s_olname) && (s_fname > s_ofname))
	{
		return true;
	}
	return false;
}

bool User::operator==(User* user)
{
	// arrays to hold other users' strings
	char other_user_fname[USER_STR_FNAME_LEN + 1];
	char other_user_lname[USER_STR_LNAME_LEN + 1];

	//null them out for safety
	memset(other_user_fname, '\0', USER_STR_FNAME_LEN + 1);
	memset(other_user_lname, '\0', USER_STR_LNAME_LEN + 1);
	
	// get other users first and last name
	user->GetFirstName(other_user_fname);
	user->GetLastName(other_user_lname);

	// std::string versions for easy comparison
	std::string s_lname(lname);
	std::string s_fname(fname);
	std::string s_olname(other_user_lname);
	std::string s_ofname(other_user_fname);


	// check for length because otherwise this case would present itself:
	// if(name == namez) { return true; }
	// this would register as true because it only checks up to the smallest strings max index

	// check if last names match in value and length
	if ((s_lname == s_olname) && (s_lname.length() == s_olname.length()))
	{
		// check if first names match in value and length
		if((s_fname == s_ofname) && (s_fname.length() == s_ofname.length()))
		{
			return true;
		}
	}
	return false;
}

void User::GetFirstName(char afname[], int code) const
{
	if (privacyCode & FNAME_bm)
	{
		if (privacyCode == code)
		{
			strcpy(afname, fname);
		}
		else
		{
			memset(afname, '\0', USER_STR_FNAME_LEN);
			memset(afname, '-', 6);
		}
	}
	else
	{
		strcpy(afname, fname);
	}
}

void User::GetLastName(char alname[], int code) const
{
	if (privacyCode & LNAME_bm)
	{
		if (privacyCode == code)
		{
			strcpy(alname, lname);
		}
		else
		{
			memset(alname, '\0', USER_STR_LNAME_LEN);
			memset(alname, '-', 6);
		}
	}
	else
	{
		strcpy(alname, lname);
	}
}

void User::GetMajor(char amajor[], int code) const
{
	if (privacyCode & MAJOR_bm)
	{
		if (privacyCode == code)
		{
			strcpy(amajor, major);
		}
		else
		{
			memset(amajor, '\0', USER_STR_MAJOR_LEN);
			memset(amajor, '-', 6);
		}
	}
	else
	{
		strcpy(amajor, major);
	}
}

void User::GetEmail(char anemail[], int code) const
{
	if (privacyCode & EMAIL_bm)
	{
		if (privacyCode == code)
		{
			strcpy(anemail, email);
		}
		else
		{
			memset(anemail, '\0', USER_STR_EMAIL_LEN);
			strcpy(anemail, "------@------");
		}
	}
	else
	{
		strcpy(anemail, email);
	}
}

void User::GetGender(char& agender, int code) const
{
	if (privacyCode & GENDER_bm)
	{
		if (privacyCode == code)
		{
			agender = gender;
		}
		else
		{
			agender = '&';
		}
	}
	else
	{
		agender = gender;
	}
}

DateType User::GetDateOfBirth(int code) const
{
	// variables to hold values while we assign values
	int day = 0;
	int month = 0;
	int year = 0;

	// check if month from date of birth requires access code
	if (privacyCode & MONTH_DOB_bm)
	{
		if (privacyCode == code)
		{
			month = dateOfBirth.GetMonth();
		}
		else
		{
			month = 0;
		}
	}
	else
	{
		month = dateOfBirth.GetMonth();
	}

	// check if day from date of birth requires access code
	if (privacyCode & DAY_DOB_bm)
	{
		if (privacyCode == code)
		{
			day = dateOfBirth.GetDay();
		}
		else
		{
			day = 0;
		}
	}
	else
	{
		day = dateOfBirth.GetDay();
	}

	// check if year from date of birth requires access code
	if (privacyCode & YEAR_DOB_bm)
	{
		if (privacyCode == code)
		{
			year = dateOfBirth.GetYear();
		}
		else
		{
			year = 0;
		}
	}
	else
	{
		year = dateOfBirth.GetYear();
	}

	// Return a DateType object with the values gathered
	return DateType(month, day, year);
}

void User::GetDateOfBirth(DateType& aDateOfBirth, int code) const
{
	aDateOfBirth = GetDateOfBirth(code);
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
	AddressType retAddress;
	GetAddress(retAddress, code);
	return retAddress;
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
			memset(aStreetName, '\0', USER_STR_STREET_LEN);
			memset(aStreetName, '-', 6);
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
			memset(aCity, '\0', USER_STR_CITY_LEN);
			memset(aCity, '-', 6);
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
			// bad code so zip is 0 to indicate a bad code
			aZip = 0;
		}
	}
	else
	{
		// don't require a code so we assign the zip
		aZip = address.zip;
	}

	// State
	// check if state requires access code (aka locked)
	if (privacyCode & STATE_bm)
	{
		// it requires access so now check if the code provided is equal to our privacy code
		if (privacyCode == code)
		{
			// codes match so we assign the real state
			strcpy(aState, address.state);
		}
		else
		{
			
			// codes don't match so we set the state to a string to indicate a bad code
			memset(aState, '\0', USER_STR_STATE_LEN);
			memset(aState, '-', USER_STR_STATE_LEN - 1);
		}
	}
	else
	{
		// code isnt required so we assign the state
		strcpy(aState, address.state);
	}

}

void User::SetFirstName(const char* afName)
{
	strcpy(fname, afName);
}

void User::SetLastName(const char* alName)
{
	strcpy(lname, alName);
}

void User::SetMajor(const char* amajor)
{
	strcpy(major, amajor);
}

void User::SetEmail(const char* anemail)
{
	strcpy(email, anemail);
}

void User::SetGender(char aGender)
{
	gender = aGender;
}

void User::SetDateOfBirth(DateType aDateOfBirth)
{
	dateOfBirth = aDateOfBirth;
}

void User::SetGPA(float aGPA)
{
	gpa = aGPA;
}

void User::SetAddress(AddressType aAddress)
{
	address = aAddress;
}

void User::SetAddress(char aStreetName[], int aStreetNo, char aCity[], int aZip, char aState[])
{
	strcpy(address.streetName, aStreetName);
	strcpy(address.city, aCity);
	strcpy(address.state, aState);
	address.streetNo = aStreetNo;
	address.zip = aZip;
}

void User::SetPrivacycode(int code)
{
	privacyCode = code;
}

void User::Display(int code) const
{
	LocalDisplay(std::cout, code);
}

void User::Display(std::ofstream& outFile, int code) const
{
	if (!outFile.good())
	{
		std::cout << "Error opening output file at line " << __LINE__ << ".\n";
	}
	else
	{
		LocalDisplay(outFile, code);
	}
}

void User::Implementer(char name[]) const
{
	strcpy(name, "Anthony Dragotta"); // Replace dashes with your first and last name.
}

void User::LocalDisplay(std::ostream& outStream, int code) const
{
	char fname[USER_STR_FNAME_LEN];
	char lname[USER_STR_LNAME_LEN];
	char major[USER_STR_MAJOR_LEN];
	char email[USER_STR_EMAIL_LEN];
	char gender;
	AddressType addr;

	GetFirstName(fname, code);
	GetLastName(lname, code);
	GetMajor(major, code);
	GetEmail(email, code);
	GetAddress(addr, code);
	GetGender(gender, code);
	AddressType tempAddr = GetAddress(code);
	DateType dob = GetDateOfBirth(code);
	
	outStream << std::string(25, '-') << std::endl;
	outStream << std::left << std::setfill(' ') << std::setw(15) << "First name:" << fname << "\n";
	outStream << std::left << std::setfill(' ') << std::setw(15) << "Last name:" << lname << "\n";
	outStream << std::left << std::setfill(' ') << std::setw(15) << "Gender:" << gender << "\n";
	outStream << std::left << std::setfill(' ') << std::setw(15) << "Major:" << major << "\n";
	
	
	outStream << std::left << std::setfill(' ') << std::setw(15) << "Address:" << std::right << tempAddr.streetNo << " " <<
		tempAddr.streetName << " " << tempAddr.city << " " << tempAddr.zip << " " << tempAddr.state << "\n";
	
	outStream << std::left << std::setfill(' ') << std::setw(15) << "GPA:" << std::right << std::fixed << std::setprecision(2) << GetGPA(code) << "\n";
	
	outStream << std::left << std::setfill(' ') << std::setw(15) << "Date of birth:" << std::right << std::setfill('0') <<
		std::setw(2) << dob.GetMonth() << "/" << std::setw(2) << dob.GetDay() << "/" << std::setw(4) <<
		dob.GetYear() << "\n";
	
	outStream << std::left << std::setfill(' ') << std::setw(15) << "Email: " << email << std::endl;
}
