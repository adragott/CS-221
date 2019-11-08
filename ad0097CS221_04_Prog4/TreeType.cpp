#include "TreeType.h"

TreeType::TreeType() : root(nullptr) {}
TreeType::~TreeType(){}


void TreeType::PutUser(User user)
{
}

void TreeType::Insert(TreeNode* tree, ItemType item)
{
}

User* TreeType::GetYoungestStudent(DateType &bdate)
{
	return nullptr;
}

void TreeType::Print(OrderType otype, std::ofstream& outfile)
{


}

void TreeType::PrintTree(TreeNode tree, std::ofstream& outfile)
{
}

void TreeType::PrintDescendants(User* user, OrderType otype, std::ofstream& outfile)
{
}

// safety check to tell if we have memory available to allocate from the heap
bool TreeType::IsFull() const
{

	TreeNode* location;
	try
	{
		location = new TreeNode;
		delete location;
		return false;
	}
	catch (std::bad_alloc exception)
	{
		return true;
	}
}

bool TreeType::IsEmpty() const
{
	return (root == nullptr);
}
