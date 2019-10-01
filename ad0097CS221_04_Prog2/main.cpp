#include "DateType.h"
#include "User.h"
#include "TestDriver.h"

#include <fstream>


using namespace std;

void CompileTest(User& user, char fn[], char ln[], char mjr[], char eml[], char& gn, DateType& db, float& gp1, AddressType& adt1, char snm[], int& sno, char ct[], int& zp, char st[], int code)
{
	int i = 0, cnt;
	TestDriver td;
	User users[50];

	cnt = td.Populate("C:\\tmp\\cs221\\hwsamplefile.txt", users);

	ofstream outfile;
	outfile.open("test.txt");
	if (!outfile) {
		cout << "Unable to open filefile.txt";
		exit(1); // terminate with error
	}

	users[0].Display(code);
	users[0].Display(outfile, code);


	if (db.GetMonth() == 10 && db.GetDay() == 10 && db.GetYear() == 10)
		i++;
	if (strcmp(adt1.streetName, "") == 0 && adt1.streetNo == 0 && strcmp(adt1.city, "") == 0 && adt1.zip == 0 && strcmp(adt1.state, "") == 0)
		i++;

	user.GetFirstName(fn, code);
	user.GetLastName(ln, code);
	user.GetMajor(mjr, code);
	user.GetEmail(eml, code);
	user.GetGender(gn, code);
	db = user.GetDateOfBirth(code);
	gp1 = user.GetGPA(code);
	adt1 = user.GetAddress(code);
	gp1 = user.GetGPA(code);
	user.GetAddress(adt1, code);
	user.GetGPA(gp1, code);
}

int main(int argc, char** argv)
{
	//User me("Penguin", "Zerenghetti", 'm', "CompSci", AddressType("street", "huntsville", "AL", 200, 35806), 4.0f, DateType(6, 20, 1997), "penguin@hotmail.com", 8193);
	//me.Display();

	//User me2;
	//me2.Display();


	TestDriver tester;
	User users[50];
	int user_count = tester.Populate(INPUT_FILE_NAME, users);

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

	tester.Test(users, user_count);
	tester.Test(outFile, users, user_count);

	outFile.clear();
	outFile.close();
	
	return 0;
}