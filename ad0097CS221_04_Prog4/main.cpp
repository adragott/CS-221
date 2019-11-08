#include <iostream>
#include "TestDriver.h"
#include "User.h"
int main(int argc, char** argv)
{
	User user("Anthony", "Dragotta", 'm', "CompSci",
		AddressType("lol", "huntsville", "AL", 345, 35806), 1.1f,
		DateType(6, 20, 1997), "snowl0l@hotmail.com", 0);
	
	User user1("Anthony", "Dragottaz", 'm', "CompSci",
		AddressType("lol", "huntsville", "AL", 345, 35806), 1.1f,
		DateType(6, 20, 1997), "snowl0l@hotmail.com", 0);

	if (user < &user1)
	{
		std::cout << "first user is alphabetically less than second user" << std::endl;
	}

	if (user > &user1)
	{
		std::cout << "first user is alphabetically greater than the second user" << std::endl;
	}

	if (user == &user1)
	{
		std::cout << "they're equal" << std::endl;
	}


	if ("abc" < "abcz")
	{
		std::cout << "before" << std::endl;
	}
	return 0;
}