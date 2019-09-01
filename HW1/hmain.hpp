#ifndef _HMAIN_HPP_
#define _HMAIN_HPP_

#include "homework.hpp"


const int NUM_LOCKERS =					9;
const int LOCKER_NAME_LEN =				10;

const char INPUT_FILE_NAME[] =	"testInput.txt";
const char OUTPUT_FILE_NAME[] =	"testOutput.txt";

enum LockerErr
{
	LE_NO_LOCKER_AVAIL =			1
};

struct Locker
{
public:
	char name[LOCKER_NAME_LEN];
	int key;
	bool resv;
private:
};

// Returns the number of empty lockers in mylockers.
int FindNoOfAvailableLockers(Locker mylockers[]);

// Returns the first available(empty) locker in mylockers.
int FindAvailableLocker(Locker mylockers[]);

// Assigns a locker for personand keeps the key for another person as nextkey for a group of people.
int DropBag(Locker mylockers[], const char* person, int nextkey);

// Find the locker for person in mylockers.
int GetLocker(Locker mylockers[], const char* person);

// Empties the locker for person after finding his or her lockerand the lockers of the people in the group if any.
void PickupBag(Locker mylockers[], const char* person);

// Faster way of running PickupBag
// After we've found the initial keyholder of a group, we know longer need to search by name because we have all the indexes
void PickupBagAtIndex(Locker mylockers[], int key);

// Displays mylockers in a simple formatand writes the result to an output stream named outfile.
void DisplayLockers(Locker mylockers[], std::ofstream &outfile);

// Reads pickupand drop information from file having name infilenameand assigns or empties the lockers accordingly.
void ReadLockerInfo(Locker mylockers[], std::ifstream& infile, std::ofstream& outfile);

// Initializes reserved field of each locker to false.
void InitializeLockers(Locker mylockers[]);


#endif