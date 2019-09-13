/*
Author:				Anthony Dragotta
Username:			ad0097
Assignment Number:	1

 -- main.cpp --

 This is the main source file for this assignment.

 -- !main.cpp --
*/

#include "hmain.hpp"
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <cstring>


int main(int argc, char** argv)
{
	static Locker lockerBank[NUM_LOCKERS];
	std::string inputFile(INPUT_FILE_NAME);
	std::string outputFile(OUTPUT_FILE_NAME);

	std::ofstream oStream;
	std::ifstream iStream;

	iStream.open(inputFile.c_str());
	if(iStream.fail())
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


	// empty all lockers
	InitializeLockers(lockerBank);
	// Read locker info inputs, handle bag requests, print out to the output file
	ReadLockerInfo(lockerBank, iStream, oStream);

	// close file streams
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
	// Get the next available locker index
	int lockerNum = FindAvailableLocker(mylockers);
	// Make sure the lockerNum is >= 0
	// If our lockerNumber is -1, there are no available lockers so we must return
	// If our lockerNumber is >= our max number of lockers, an error has occured
	// The second part of the comparison is purely for error checking.
	if (lockerNum < 0 || lockerNum >= NUM_LOCKERS)
	{
		// Return the bad lucker number as -1 to indicate that no lockers were available
		return lockerNum;
	}
	// Fill the locker
	FillLocker(&mylockers[lockerNum], person, nextkey);
	// Return the key of the locker the bag was assigned to
	return lockerNum;
}

// Find the locker key for person in mylockers.
int GetLockerKey(Locker mylockers[], const char* person)
{
	int retKey = -1;
	for (int ind = 0; ind < NUM_LOCKERS; ind++)
	{
		// If our person argument matches the person assigned to the locker, we have the locker we want
		if (std::string(person) == std::string(mylockers[ind].name))
		{
			// Assign our return key as the index
			retKey = ind;
			break;
		}
	}
	return retKey;
}

// Empties the locker for person after finding his or her lockerand the lockers of the people in the group if any.
void PickupBag(Locker mylockers[], const char* person)
{
	// Get the locker key associated with the person arg supplied
	int key = GetLockerKey(mylockers, person);
	// Make sure we found a locker associated with the person
	// Second part if this check is purely for error checking
	if (key >= 0 && key < NUM_LOCKERS)
	{
		// Pickup the bag at the key found for person
		PickupBagAtIndex(mylockers, key);
	}
	else
	{
		std::cout << "Error trying to pick up " << std::string(person) << "'s bag" << std::endl;
		// error
	}

}

// Faster way of running PickupBag
// After we've found the initial keyholder of a group, we know longer need to search by name because we have all the indexes we need
void PickupBagAtIndex(Locker lockers[], int key)
{
	// Make sure our lockers pointer is not null
	if (!lockers)
	{
		std::cout << "Error" << std::endl;
		return;
	}
	// Make sure the key provided is valid
	if (key >= NUM_LOCKERS || key < 0)
	{
		std::cout << "Error: Key invalid at " << __LINE__ << " " << std::endl;
		// error
	}
	// Make sure the locker is marked as in use
	else if (!lockers[key].resv)
	{
		std::cout << "Error" << std::endl;
		// error
	}
	else
	{
		// Check if this locker is part of a group
		if (lockers[key].key >= 0)
		{
			// This locker is a part of a group so we need to pick up the bag in the locker using the key being stored in this locker
			// PickupBagAtIndex is a recursive call when the lockers key is not -1,
			// so we need to do one check to make sure our stack doesn't overflow
			// This check is here to prevent crashes in the event of some error on my part
			if (key == lockers[key].key)
			{
				std::cout << "Error: Attempting to recursively call " << __FUNCTION__ << " at " << __LINE__ << " an infinite amount of times" << std::endl;
				return;
			}
			PickupBagAtIndex(lockers, lockers[key].key);
		}
		//std::cout << "Picking up " << lockers[key].name << "'s bag" << std::endl;
		EmptyLocker(&lockers[key]);
	}
}

// Displays mylockers in a simple formatand writes the result to an output stream named outfile.
// Function provided by Dr. Aygün
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
	while (!infile.eof())
	{
		// buff - buffer used to hold lines being read from our file
		char buff[256];
		// read a \n terminated line from our input stream
		infile.getline(buff, 256);

		// Make sure our line was valid
		if (isalpha(buff[0]))
		{
			// String stream to hold each line read from our file
			std::istringstream ifss(buff);
			// action - Decides whether our person is picking a bag up or dropping a bag off
			// Ideally action can only be "drop" or "pickup"
			std::string action;
			// name - name of the person dropping off or picking up
			std::string name;
			// Read the first word from our string stream
			ifss >> action;
			if (action == "drop")
			{
				// drop_num - Number of bags being dropped off
				int drop_num = 0;
				// Read the next int into drop_num from our string stream
				ifss >> drop_num;
				// drop_num validity check
				if ((drop_num >= 1) && (drop_num <= NUM_LOCKERS))
				{
					// Check and make sure we have enough lockers available to support the amount of bags being dropped off
					int num_lockers_available = FindNoOfAvailableLockers(mylockers);
					if (num_lockers_available >= drop_num)
					{
						// previousKey -- holds the key previously returned by DropBag
						int previousKey = -1;
						// Start a loop iterating the number of bags we need dropped off
						for (int x = 0; x < drop_num; x++)
						{
							// Read the first name from our string stream
							ifss >> name;
							//std::cout << "Dropping off " << name << "'s bag" << std::endl;
							// DropBag returns the key of the locker the bag was assigned to
							// If DropBag returns -1, it means our bag was a failure
							// We should never actually get a -1 return value because we check beforehand whether or not
							// we can support the number of bags requested.
							if ((previousKey = DropBag(mylockers, name.c_str(), previousKey)) < 0)
							{
								std::cout << "Error Couldn't add bag. There are no bags available." << std::endl;
							}
						}
					}
					// If we don't have enough lockers available to support the number of bags being dropped off,
					// we need to print that to the output file
					else
					{
						outfile << "Couldn't add " << drop_num << (drop_num > 1 ? " bags" : " bag") << ". Only " 
							<< num_lockers_available << (num_lockers_available > 1 ? " lockers" : " locker") << " available.\n";
					}
				}
				// This error is only thrown if the number of bags to be dropped off read from the file is wrong
				// We should never get here
				else
				{
					std::cout << "Invalid input. We don't support " << drop_num << " lockers." << std::endl;
				}
			}
			else if (action == "pickup")
			{
				// Read the name of the person picking up their bag from the string stream
				ifss >> name;
				// Picks up bag for the person requested
				// If the person is a part of a group, it will handle those bags as well
				PickupBag(mylockers, name.c_str());
			}
			// if we get here, it means there was an error reading from the input file. 
			// Make sure the input file is correct
			else
			{
				// error unknown action input
			}
			// After a successful bag transaction (either a pickup or drop off) we print our table of bags and people to the output file
			DisplayLockers(mylockers, outfile);
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
