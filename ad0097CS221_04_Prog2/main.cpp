#include "DateType.h"
#include "User.h"
#include "TestDriver.h"

#include <fstream>
// IO file names
static const char* INPUT_FILE_NAME = "input.txt";
static const char* OUTPUT_FILE_NAME = "output.txt";

int main(int argc, char** argv)
{
	User me("Penguin", "Zerenghetti", 'm', "CompSci", AddressType("street", "huntsville", "AL", 200, 35806), 4.0f, DateType(6, 20, 1997), "penguin@hotmail.com", 8193);
	me.Display();

	User me2;
	me2.Display();


	TestDriver tester;
	User users[10];
	tester.Populate(INPUT_FILE_NAME, users);

	std::ofstream outFile;
	outFile.open(OUTPUT_FILE_NAME);
	if (outFile.fail())
	{
		outFile.clear();
		outFile.close();
		std::cout << "Error opening output file: " << OUTPUT_FILE_NAME << std::endl;
		std::cout << "Exiting..." << std::endl;
		return -1;
	}
	
	return 0;
}