#include <iostream>
#include "TestDriver.h"
#include "User.h"
#include "TreeType.h"

int main()
{
	TreeType treeUsers;
	TestDriver tester;
	User* user;
	//-- Print the tree
	tester.Populate("C:\\tmp\\cs221\\hw1\\input.txt",
		treeUsers);
	std::cout << "\n\nPrinting in preorder" << std::endl;
	treeUsers.Print(PREORDER,"C:\\tmp\\cs221\\hw1\\raygunhw3samplefilePREORDER.txt");
	std::cout << "\n\nPrinting in order" << std::endl;
	treeUsers.Print(INORDER,"C:\\tmp\\cs221\\hw1\\raygunhw3samplefileINORDER.txt");
	std::cout << "\n\nPrinting descendants in post order" << std::endl;
	treeUsers.Print(POSTORDER, "C:\\tmp\\cs221\\hw1\\raygunhw3samplefilePOSTORDER.txt");
	//-- Find the user with the highest GPA
	//DateType bdate;
	//user = treeUsers.GetYoungestStudent(bdate);
	//user->Display(8213479);
	////-- Print the descendants of the user with the highest GPA
	//
	//treeUsers.PrintDescendants(user, PREORDER, "C:\\tmp\\cs221\\hw3\\raygunhw3samplefileDescendantsPREORDER.txt");
	//
	//treeUsers.PrintDescendants(user, INORDER, "C:\\tmp\\cs221\\hw3\\raygunhw3samplefileDescendantsINORDER.txt");
	//
	//treeUsers.PrintDescendants(user, POSTORDER,
	//	"C:\\tmp\\cs221\\hw3\\raygunhw3samplefileDescendantsPOSTORDER.txt");
	//tester.Test("C:\\tmp\\cs221\\hw3\\raygunhw3testing.txt", treeUsers);
	return 0;

}