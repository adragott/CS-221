#include "TreeType.h"

TreeType::TreeType() : root(nullptr) {}
TreeType::~TreeType(){}


void TreeType::PutUser(User* user)
{
	if (user == nullptr)
	{
		// bad user pass
	}


}

void TreeType::Insert(TreeNode* tree, User &user)
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

int TreeType::GetLength() const
{
	return 0;
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

User* TreeType::GetUser(User user, bool& found)
{
	Retrieve(root, user, found);
	return (User*)&user;
}

int TreeType::CountNodes(TreeNode* tree)
{
	if (tree == nullptr)
	{
		return 0;
	}
	return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

void TreeType::Retrieve(TreeNode* tree, User &user, bool& found)
{
	if (tree == nullptr)
	{
		found = false;
	}
	else if (user < tree->user)
	{
		Retrieve(tree->left, user, found);
	}
	else if (user > tree->user)
	{
		Retrieve(tree->right, user, found);
	}
	else
	{
		user = *tree->user;
		found = true;
	}
}
