#include "TestDriver.h"
#include "User.h"
#include <fstream>
#include <sstream>

TestDriver::TestDriver() {}
TestDriver::~TestDriver() {}

int TestDriver::Populate(const char* input, User users[])
{
	// Count that will be returned
	int count = 0;

	std::ifstream iStream;

	iStream.open(input);
	if (iStream.fail())
	{
		iStream.clear();
		iStream.close();
		std::cout << "Error opening input file: " << input << std::endl;
		std::cout << "Exiting..." << std::endl;
		iStream.clear();
		iStream.close();
		return -1;
	}
	int user_num = 0;
	while (!iStream.eof() && user_num <= 10)
	{
		char read_buffer[256];
		int line_num = 0;

		// Address variables here since they need to be added as a group
		char state[STR_STATE_LEN];
		char city[STR_CITY_LEN];
		int strnum = 0;
		char strname[STR_STREET_LEN];
		int zip = 0;

		// There will always be 13 fields + 1 separator
		while(line_num < 14 && !iStream.eof())
		{
			memset(read_buffer, '\0', 256);
			iStream.getline(read_buffer, 256);
			if (isalpha(read_buffer[0]))
			{
				std::istringstream ifss(read_buffer);
				std::string field_name;
				ifss >> field_name;
				field_name = field_name.substr(0, field_name.find(":"));
				if (field_name == std::string("FirstName"))
				{
					std::string fname;
					ifss >> fname;
					users[user_num].SetFirstName(fname.c_str());
				}
				else if (field_name == std::string("LastName"))
				{
					std::string lname;
					ifss >> lname;
					users[user_num].SetLastName(lname.c_str());
				}
				else if (field_name == std::string("Major"))
				{
					std::string major;
					ifss >> major;
					users[user_num].SetMajor(major.c_str());
				}
				else if (field_name == std::string("Gender"))
				{
					char gender;
					ifss >> gender;
					users[user_num].SetGender(gender);
				}
				else if (field_name == std::string("Email"))
				{
					std::string email;
					ifss >> email;
					users[user_num].SetEmail(email.c_str());
				}
				else if (field_name == std::string("GPA"))
				{
					float gpa;
					ifss >> gpa;
					users[user_num].SetGPA(gpa);
				}
				else if (field_name == std::string("BirthDate"))
				{
					int month, day, year;
					ifss >> month >> day >> year;
					users[user_num].SetDateOfBirth(DateType(month, day, year));
				}
				else if (field_name == std::string("Privacy"))
				{
					int privacy;
					ifss >> privacy;
					users[user_num].SetPrivacycode(privacy);
				}
				else if (field_name == std::string("StreetName"))
				{
					// ignore initial space
					ifss.ignore(30, ' ');
					// getline instead of >> in case the street name has spaces
					ifss.getline(strname, STR_STREET_LEN);

				}
				else if (field_name == std::string("StreetNo"))
				{
					ifss >> strnum;
				}
				else if (field_name == std::string("City"))
				{
					// ignore initial space
					ifss.ignore(30, ' ');
					// getline instead of >> in case the city has spaces
					ifss.getline(city, STR_CITY_LEN);
				}
				else if (field_name == std::string("State"))
				{
					
					ifss >> state;
				}
				else if (field_name == std::string("Zip"))
				{
					ifss >> zip;
				}
				else
				{
					std::cout << "caught bad string: " << field_name << std::endl;
				}
			}
			else if(read_buffer[0] == '-' && line_num == 13)
			{
				// debugging checkpoint
			}
			else
			{
				// some error has occured or a blank line was picked up
				continue;
			}
			line_num++;
		}
		users[user_num++].SetAddress(AddressType(strname, city, state, strnum, zip));
	}
	iStream.close();
	return user_num;
}

// need to check and make sure all functions work
// basically testing this classes functionality
void TestDriver::Test(User users[], int count)
{
	for (int ind = 0; ind < count; ind++)
	{
		users[ind].Display(TRUE_CODE);
	}
}

// preconditions: 
// outFile is an already opened stream that is in a good state
// users is not null
void TestDriver::Test(std::ofstream& outFile, User users[], int count)
{
	// make sure stream is A OKAY
	if (!outFile.is_open() || !outFile.good())
	{
		std::cout << "Output stream isn't open... Exiting...\n";
		exit(1);
	}

	for (int ind = 0; ind < count; ind++)
	{
		users[ind].Display(outFile, TRUE_CODE);
	}
}
