#include "hmain.hpp"
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <cstring>

static Locker lockerBank[NUM_LOCKERS];
int main(int argc, char** argv)
{
	std::string inputFile(INPUT_FILE_NAME);
	std::string outputFile(OUTPUT_FILE_NAME);

	std::ofstream oStream;
	std::ifstream iStream;

	iStream.open(inputFile);
	if(iStream.bad())
	{
		std::cout << "Error opening input file: " << inputFile << std::endl;
		std::cout << "Exiting..." << std::endl;
		return -1;
	}

	
	oStream.open(outputFile);
	if (oStream.bad())
	{
		std::cout << "Error opening output file: " << outputFile << std::endl;
		std::cout << "Exiting..." << std::endl;
		return -1;
	}

	

	InitializeLockers(lockerBank);
	ReadLockerInfo(lockerBank, iStream, oStream);


	iStream.close();
	oStream.close();
	
	return 0;
}
// Returns the number of empty lockers in mylockers.
int FindNoOfAvailableLockers(Locker mylockers[])
{
	int ret = 0;
	for (int ind = 0; ind < NUM_LOCKERS; ind++)
	{
		if (!mylockers[ind].resv)
		{
			ret++;
		}
	}
	return ret;
}

// Returns the first available(empty) locker in mylockers.
int FindAvailableLocker(Locker mylockers[])
{
	int ret = -1;
	for (int x = 0; x < NUM_LOCKERS; x++)
	{
		if (!mylockers[x].resv)
		{
			ret = x;
			break;
		}
	}
	return ret;
}

// Assigns a locker for personand keeps the key for another person as nextkey for a group of people.
int DropBag(Locker mylockers[], const char* person, int nextkey = -1)
{
	int lockerNum = FindAvailableLocker(mylockers);
	if (lockerNum < 0 || lockerNum >= NUM_LOCKERS)
	{
		return lockerNum;
	}

	// Fill the locker
	memcpy(mylockers[lockerNum].name, person, strlen(person));
	mylockers[lockerNum].resv = true;
	mylockers[lockerNum].key = nextkey;


	return lockerNum;
}

// Find the locker for person in mylockers.
int GetLocker(Locker mylockers[], const char* person)
{
	int retIndex = -1;
	for (int ind = 0; ind < NUM_LOCKERS; ind++)
	{
		if (std::string(person) == std::string(mylockers[ind].name))
		{
			retIndex = ind;
			break;
		}
	}
	return retIndex;
}

// Empties the locker for person after finding his or her lockerand the lockers of the people in the group if any.
void PickupBag(Locker mylockers[], const char* person)
{
	volatile int key = GetLocker(mylockers, person);
	if (key >= 0 && key < NUM_LOCKERS)
	{
		if (mylockers[key].key >= 0)
		{
			PickupBag(mylockers, mylockers[mylockers[key].key].name);
		}
		mylockers[key].key = -1;
		mylockers[key].resv = false;
		memset(mylockers[key].name, '\0', LOCKER_NAME_LEN);
	}
	else
	{
		std::cout << "Error trying to pick up " << std::string(person) << "'s bag" << std::endl;
		// error
	}

}


// Faster way of running PickupBag
// After we've found the initial keyholder of a group, we know longer need to search by name because we have all the indexes
void PickupBagAtIndex(Locker mylockers[], int key)
{
	if (key >= NUM_LOCKERS || key < 0)
	{
		std::cout << "Error" << std::endl;
		// error
	}
	else if (!mylockers[key].resv)
	{
		std::cout << "Error" << std::endl;
		// error
	}
	else
	{
		if (mylockers[key].key >= 0)
		{
			PickupBagAtIndex(mylockers, key);
		}
		mylockers[key].key = -1;
		mylockers[key].resv = false;
		memset(mylockers[key].name, '\0', LOCKER_NAME_LEN);
	}
}

// Displays mylockers in a simple formatand writes the result to an output stream named outfile.
void DisplayLockers(Locker mylockers[], std::ofstream &outfile)
{
	int i, j;
	for (i = 0; i < NUM_LOCKERS; i++)
	{
		if (i % 3 == 0)
		{
			outfile << std::endl;
			for (j = 0; j < 62; j++)
			{
				outfile << "_";
			}
			outfile << std::endl;
		}
		if (mylockers[i].resv)
		{
			if (mylockers[i].key >= 0)
			{
				outfile << " " << i << ")" << std::setw(10) << mylockers[i].name << " . " << std::setw(2) << mylockers[i].key << " | ";
			}
			else
			{
				outfile << " " << i << ")" << std::setw(10) << mylockers[i].name << " . " << std::setw(5) <<  " | ";
			}
			
		}	
		else
		{
			outfile << " " << i << ")" << std::setw(10) << " " << " . " << std::setw(2) << " " << " | ";
		}
	}
	outfile << std::endl;
	for (j = 0; j < 62; j++)
	{
		outfile << "_";
	}
	outfile << "\n\n";
}

// Reads pickupand drop information from file having name infilenameand assigns or empties the lockers accordingly.
void ReadLockerInfo(Locker mylockers[], std::ifstream &infile, std::ofstream &outfile)
{
	std::cout << "Reading input file\n";
	while (!infile.eof())
	{
		char buff[256];
		std::cout << "Number available lockers: " << FindNoOfAvailableLockers(mylockers) << std::endl;
		infile.getline(buff, 256);

		// Make sure our line was valid
		if (isalpha(buff[0]))
		{
			//std::cout << "LINE: " << std::string(buff) << std::endl;
			std::istringstream ifss(buff);
			std::string action;
			int nArg = 0;
			std::string name;
			ifss >> action;
			std::cout << "Action: " << action << "\t";
			if (action == "drop")
			{
				ifss >> nArg;
				std::cout << "Num Arg: " << nArg << "\t";
				if (nArg <= 0)
				{
					std::cout << "ERROR: Can't " << action << " " << nArg << " bags off..." << std::endl;
					continue;
				}
				else
				{
					int previousKey = -1;
					if (nArg > 1)
					{
						if (FindNoOfAvailableLockers(mylockers) >= nArg)
						{
							for (int x = 0; x < nArg; x++)
							{
								ifss >> name;
								// here we process the bag with the name
								std::cout << "Name: " << name << "\t";
								int nextKey = -1;
								if ((nextKey = DropBag(mylockers, name.c_str(), previousKey)) < 0)
								{
									std::cout << "Error Couldn't add bag. There are no bags available." << std::endl;
								}
								else
								{
									previousKey = nextKey;
									std::cout << "key value: " << nextKey << std::endl;
								}
								DisplayLockers(mylockers, outfile);
							}
						}
					}
					else
					{
						if (FindNoOfAvailableLockers(mylockers) > 0)
						{
							ifss >> name;
							std::cout << "Name: " << name << "\t";
							DropBag(mylockers, name.c_str());
							DisplayLockers(mylockers, outfile);
						}
						else
						{
							std::cout << "No lockers available? " << FindNoOfAvailableLockers(mylockers) << std::endl;
						}
					}

				}
			}
			else if (action == "pickup")
			{
				ifss >> name;
				std::cout << "Name: " << name << "\t";
				PickupBag(mylockers, name.c_str());
				DisplayLockers(mylockers, outfile);
			}
			else
			{
				// error unknown action input
			}
			std::cout << std::endl;
		}
	}
}

// Initializes reserved field of each locker to false.
void InitializeLockers(Locker mylockers[])
{
	for (int ind = 0; ind < NUM_LOCKERS; ind++)
	{
		mylockers[ind].key = -1;
		mylockers[ind].resv = false;
		memset(mylockers[ind].name, '\0', LOCKER_NAME_LEN);
	}
}
