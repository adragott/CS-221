#include "TestDriver.h"
#include <iostream>
#include <fstream>
#include <sstream>

TestDriver::TestDriver()
{

}

TestDriver::~TestDriver()
{

}

int TestDriver::Populate(const char* input, TreeType& treeUsers) const
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
	while (!iStream.eof())
	{
		User tempUser;
		char read_buffer[256];
		int line_num = 0;

		// There will always be 9 fields + 1 separator
		while (line_num <= 9 && !iStream.eof())
		{
			memset(read_buffer, '\0', 256);
			iStream.getline(read_buffer, 256);
			if (isalpha(read_buffer[0]))
			{
				std::istringstream ifss(read_buffer);
				std::string field_name;
				ifss >> field_name;
				field_name = field_name.substr(0, field_name.find(":"));
				if (iStream.eof())
				{
					//break;
				}
				else if (field_name == std::string("FirstName"))
				{
					std::string fname;
					ifss >> fname;
					tempUser.SetFirstName(fname.c_str());
				}
				else if (field_name == std::string("LastName"))
				{
					std::string lname;
					ifss >> lname;
					tempUser.SetLastName(lname.c_str());
				}
				else if (field_name == std::string("Major"))
				{
					std::string major;
					ifss >> major;
					tempUser.SetMajor(major.c_str());
				}
				else if (field_name == std::string("Gender"))
				{
					char gender;
					ifss >> gender;
					tempUser.SetGender(gender);
				}
				else if (field_name == std::string("Email"))
				{
					std::string email;
					ifss >> email;
					tempUser.SetEmail(email.c_str());
				}
				else if (field_name == std::string("GPA"))
				{
					float gpa;
					ifss >> gpa;
					tempUser.SetGPA(gpa);
				}
				else if (field_name == std::string("BirthDate"))
				{
					int month, day, year;
					ifss >> month >> day >> year;
					tempUser.SetDateOfBirth(DateType(month, day, year));
				}
				else if (field_name == std::string("Privacy"))
				{
					int privacy;
					ifss >> privacy;
					tempUser.SetPrivacycode(privacy);
				}
				else if (field_name == std::string("Address"))
				{
					int temp_zip = 0;
					int temp_strt_no = 0;
					std::string temp_strt_name;
					std::string temp_city;
					std::string temp_state;

					ifss >> temp_strt_no >> temp_strt_name >> temp_city >> temp_zip >> temp_state;
					tempUser.SetAddress(AddressType(temp_strt_name.c_str(), temp_city.c_str(), temp_state.c_str(), temp_strt_no, temp_zip));
				}
				else
				{
					// The last user still had the State field so I included this.
					std::cout << "\ncaught bad field: " << field_name << std::endl;
					std::cout << "Is the input file correct?\n\n";
					continue;
				}
			}
			else if (read_buffer[0] == '-')
			{
				// debugging checkpoint
				treeUsers.PutUser(&tempUser);
			}
			else
			{
				// some error has occured or a blank line was picked up
				continue;
			}
			line_num++;
		}
		user_num++;
	}
	iStream.close();
	return user_num;
return 0;
}

void TestDriver::Test(std::ofstream& outFile, TreeType& treeUsers) const
{
	treeUsers.Print(PREORDER, dynamic_cast<std::ofstream&>(std::cout));
	treeUsers.Print(POSTORDER, dynamic_cast<std::ofstream&>(std::cout));
	treeUsers.Print(INORDER, dynamic_cast<std::ofstream&>(std::cout));

}

void TestDriver::Test(const char* output_file_name, TreeType& treeUsers) const
{
	std::ofstream output_stream;
	output_stream.open("input_file_name");
	if (!output_stream.fail())
	{
		std::cout << "failed to open output file " << output_file_name << " at line " << __LINE__ << std::endl;
		return;
	}
	Test(output_stream, treeUsers);

}
