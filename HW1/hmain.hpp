#ifndef _HMAIN_HPP_
#define _HMAIN_HPP_

#include "homework.hpp"


const int NUM_LOCKERS =			9;
const int LOCKER_NAME_LEN =		10;

const char INPUT_FILE_NAME[] =	"testInput.txt";
const char OUTPUT_FILE_NAME[] =	"testOutput.txt";

struct Locker
{
	char name[LOCKER_NAME_LEN];
	int key;
	bool resv;
};

// Returns the number of empty lockers in mylockers.
int FindNoOfAvailableLockers(Locker mylockers[]);

// Returns the first available(empty) locker in mylockers.
int FindAvailableLocker(Locker mylockers[]);

// Assigns a locker for person and keeps the key for another person as nextkey for a group of people.
// Returns the index (key) of the locker the bag was assigned to
// If There were no available lockers available, -1 is returned
int DropBag(Locker mylockers[], const char* person, int nextkey);

// Find the locker index for person in mylockers.
int GetLockerKey(Locker mylockers[], const char* person);

// Empties the locker for person after finding his or her lockerand the lockers of the people in the group if any.
void PickupBag(Locker mylockers[], const char* person);

// Faster way of running PickupBag
// After we've found the initial keyholder of a group, we know longer need to search by name because we have all the indexes
void PickupBagAtIndex(Locker lockers[], int key);

// Displays mylockers in a simple formatand writes the result to an output stream named outfile.
void DisplayLockers(Locker mylockers[], std::ofstream &outfile);

// Reads pickupand drop information from file having name infilenameand assigns or empties the lockers accordingly.
void ReadLockerInfo(Locker mylockers[], std::ifstream& infile, std::ofstream& outfile);

// Initializes reserved field of each locker to false.
void InitializeLockers(Locker mylockers[]);

// Empties a locker
// Marks the locker as available, sets its key to -1, and nulls its name
void EmptyLocker(Locker* locker);

// Fills locker
// Marks locker as unavailable
// Sets its key to the nextKey if one is provided, otherwise it defaults to -1
// Sets the lockers name to the name provided
void FillLocker(Locker* locker, const char* person, int nextKey);


#endif