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

	while (!iStream.eof())
	{
		char read_buffer[256];
		int line_num = 0;
		User tempUser;
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
				std::cout << field_name << std::endl;
				if (field_name == std::string("FirstName"))
				{

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
	}
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
