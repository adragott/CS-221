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
		char strname[30];
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
					// getline instead of >> in case the street name has spaces
					ifss.getline(strname, STR_STREET_LEN);

				}
				else if (field_name == std::string("StreetNo"))
				{
					ifss >> strnum;
				}
				else if (field_name == std::string("City"))
				{
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
				std::cout << read_buffer << std::endl;
			}
			else
			{
				// some error has occured or a blank line was picked up
				continue;
			}
			line_num++;
		}
		users[user_num].SetAddress(AddressType(strname, city, state, strnum, zip));
	}
	std::cout << "Number of users: " << user_num << std::endl;
	return 0;
}

void TestDriver::Test(User users[], int count)
{
	std::ofstream oStream;
	Test(oStream, users, count);
}

void TestDriver::Test(std::ofstream& outFile, User users[], int count)
{



}
