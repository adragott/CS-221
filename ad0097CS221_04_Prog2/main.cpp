#include "DateType.h"
#include "User.h"

#include <fstream>

static const char* INPUT_FILE_NAME = "input.txt";
static const char* OUTPUT_FILE_NAME = "output.txt";

int main(int argc, char** argv)
{
	User me("Penguin", "Zerenghetti", 'm', "CompSci", AddressType("street", "huntsville", "AL", 200, 35806), 4.0f, DateType(6, 20, 1997), "penguin@hotmail.com", 8193);
	me.Display();

	User me2;
	me2.Display();
	std::string inputFile(INPUT_FILE_NAME);
	std::string outputFile(OUTPUT_FILE_NAME);

	std::ofstream oStream;
	std::ifstream iStream;

	iStream.open(inputFile.c_str());
	if (iStream.fail())
	{
		iStream.clear();
		iStream.close();
		std::cout << "Error opening input file: " << inputFile << std::endl;
		std::cout << "Exiting..." << std::endl;
		iStream.clear();
		iStream.close();
		return -1;
	}

	oStream.open(outputFile);
	if (oStream.fail())
	{
		oStream.clear();
		oStream.close();
		std::cout << "Error opening output file: " << outputFile << std::endl;
		std::cout << "Exiting..." << std::endl;
		return -1;
	}

	
	return 0;
}