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
	for (int ind = 0; ind < NUM_LOCKERS; ind++)
	{
		if (!mylockers[ind].resv)
		{
			ret = ind;
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
	FillLocker(&mylockers[lockerNum], person, nextkey);
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
	int key = GetLocker(mylockers, person);
	if (key >= 0 && key < NUM_LOCKERS)
	{
		PickupBagAtIndex(mylockers, key);
	}
	else
	{
		std::cout << "Error trying to pick up " << std::string(person) << "'s bag" << std::endl;
		// error
	}

}


// Faster way of running PickupBag
// After we've found the initial keyholder of a group, we know longer need to search by name because we have all the indexes
void PickupBagAtIndex(Locker* lockers, int key)
{
	if (!lockers)
	{
		std::cout << "Error" << std::endl;
		return;
	}
	if (key >= NUM_LOCKERS || key < 0)
	{
		std::cout << "Error" << std::endl;
		// error
	}
	else if (!lockers[key].resv)
	{
		std::cout << "Error" << std::endl;
		// error
	}
	else
	{
		if (lockers[key].key >= 0)
		{
			PickupBagAtIndex(lockers, lockers[key].key);
		}
		std::cout << "Picking up " << lockers[key].name << "'s bag" << std::endl;
		EmptyLocker(&lockers[key]);
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
		infile.getline(buff, 256);

		// Make sure our line was valid
		if (isalpha(buff[0]))
		{
			std::istringstream ifss(buff);
			std::string action;
			int nArg = 0;
			std::string name;
			ifss >> action;
			if (action == "drop")
			{
				ifss >> nArg;
				// input no. validity check
				if (nArg >= 1 && nArg <= NUM_LOCKERS)
				{
					int num_lockers_available = FindNoOfAvailableLockers(mylockers);
					if (num_lockers_available >= nArg)
					{
						int previousKey = -1;
						for (int x = 0; x < nArg; x++)
						{
							ifss >> name;
							// here we process the bag with the name
							std::cout << "Dropping off " << name << "'s bag" << std::endl;

							if ((previousKey = DropBag(mylockers, name.c_str(), previousKey)) < 0)
							{
								std::cout << "Error Couldn't add bag. There are no bags available." << std::endl;
							}
						}
					}
					else
					{
						outfile << "Couldn't add " << nArg << (nArg > 1 ? " bags" : " bag") << ". Only " 
							<< num_lockers_available << (num_lockers_available > 1 ? " lockers" : " locker") << " available.\n";
					}
				}
				else
				{
					std::cout << "Invalid input. We don't support " << nArg << " lockers." << std::endl;
				}
			}
			else if (action == "pickup")
			{
				ifss >> name;
				PickupBag(mylockers, name.c_str());
			}
			else
			{
				// error unknown action input
			}
			DisplayLockers(mylockers, outfile);
			std::cout << std::endl;
		}
	}
}

// Initializes reserved field of each locker to false.
void InitializeLockers(Locker mylockers[])
{
	for (int ind = 0; ind < NUM_LOCKERS; ind++)
	{
		EmptyLocker(&mylockers[ind]);
	}
}


void EmptyLocker(Locker* locker)
{
	if (!locker)
	{
		// err
		return;
	}
	memset(locker->name, '\0', LOCKER_NAME_LEN);
	locker->key = -1;
	locker->resv = false;
}

void FillLocker(Locker* locker, const char* person, int nextKey = -1)
{
	if (!locker)
	{
		// err
		return;
	}
	memcpy(locker->name, person, strlen(person));
	locker->key = nextKey;
	locker->resv = true;
}
