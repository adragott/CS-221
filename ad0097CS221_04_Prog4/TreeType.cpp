#include "TreeType.h"


TreeType::TreeType()
{

}

TreeType::~TreeType()
{
	PurgeTree();
}



void TreeType::PutUser(User* user)
{
	std::cout << "Adding user: " << user->GetFirstName() << std::endl;
	if (user == nullptr)
	{
		// bad user pass
		std::cout << "null user passed at line " << __LINE__ << std::endl;
		return;
	}

	Insert(root, user);
}

void TreeType::Insert(TreeNode*& tree, User* user)
{
	if (tree == nullptr)
	{
		tree = new TreeNode(*user);
	}
	else if (*user < tree->user)
	{
		Insert(tree->left, user);
	}
	else
	{
		Insert(tree->right, user);
	}

}

User* TreeType::GetYoungestStudent(DateType &bdate)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	TreeNode* beacon_node = nullptr;
	beacon_node = RetrieveNodeOfYoungestUser(root, bdate);
	return beacon_node->user;
}

void TreeType::RetrieveNodeOfYoungestUser(TreeNode* node, DateType &bdate, TreeNode* ret_node)
{
	if (node == nullptr)
	{
		return;
	}
	else if (bdate.ComparedTo(node->user->GetDateOfBirth) == LESS)
	{

		RetrieveNodeOfYoungestUser(node->left, bdate,
	}


	

}

void TreeType::Print(OrderType otype, std::ofstream& outfile)
{

	if (!outfile.is_open())
	{
		// outfile needs to be open already!
		std::cout << "outfile not opened!\r\n";
	}

	switch (otype)
	{
		case PREORDER:
		{
			PreOrderPrint(root, outfile);
			break;
		}
		case INORDER:
		{
			InOrderPrint(root, outfile);
			break;
		}
		case POSTORDER:
		{
			PostOrderPrint(root, outfile);
			break;
		}
		default:
		{

			// shot missed
			break;
		}
	};
}

void TreeType::Print(OrderType otype, const char* output_file_name)
{
	std::ofstream output_stream;
	output_stream.open(output_file_name);
	if (!output_stream.fail())
	{
		Print(otype, output_stream);
	}
	else
	{
		std::cout << "Error opening " << output_file_name << " at line " << __LINE__ << std::endl;
		output_stream.clear();
		output_stream.close();
		return;
	}
	output_stream.close();
}

int TreeType::GetLength() const
{
	return CountNodes(root);
}

// find user in tree and then print
void TreeType::PrintDescendants(User* user, OrderType otype, std::ofstream& outfile)
{
	if (user == nullptr)
	{
		// bad user
		return;
	}

	if (!outfile.is_open())
	{
		std::cout << "Output stream isnt open . bad \r\n";
		return;
	}

	// Copy of the user we will use to compare
	User searchUser = *user;
	// TreeNode pointer used to point to the node of the user if found
	TreeNode* node_of_user = nullptr;
	RetrieveNodeOfUser(root, searchUser, node_of_user);
	if (node_of_user == nullptr)
	{
		std::cout << "User " << user->GetFirstName() << " " << user->GetLastName() << " was not found." << std::endl;
		return;
	}

	switch(otype)
	{
		case PREORDER:
		{
			// traverse the left subtree
			PreOrderPrint(node_of_user->left, outfile);
			// traverse the right subtree
			PreOrderPrint(node_of_user->right, outfile);
			break;
		}
		case INORDER:
		{
			// traverse the left subtree
			InOrderPrint(node_of_user->left, outfile);
			// traverse the right subtree
			InOrderPrint(node_of_user->right, outfile);
			break;
		}
		case POSTORDER:
		{
			// traverse the left subtree
			PostOrderPrint(node_of_user->left, outfile);
			// traverse the right subtree
			PostOrderPrint(node_of_user->right, outfile);
			break;
		}
		default:
		{
			// uh oh
			break;
		}
	}
}

void TreeType::PrintDescendants(User* user, OrderType otype, const char* output_file_name)
{
	std::ofstream output_stream;
	output_stream.open(output_file_name);
	if (!output_stream.fail())
	{
		PrintDescendants(user, otype, output_stream);
	}
	else
	{
		std::cout << "Error opening " << output_file_name << " at line " << __LINE__ << std::endl;
		output_stream.clear();
		output_stream.close();
	}
	output_stream.close();
	
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

User* TreeType::GetUser(User &user, bool& found)
{
	TreeNode* node = nullptr;
	User searchUser = user;
	RetrieveNodeOfUser(root, searchUser, node);
	if (node == nullptr)
	{
		std::cout << "User " << user.GetFirstName() << " " << user.GetLastName() << " was not found." << std::endl;
		return nullptr;
	}
	return node->user;
}

int TreeType::CountNodes(TreeNode* tree) const
{
	if (tree == nullptr)
	{
		return 0;
	}
	return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

void TreeType::RetrieveNodeOfUser(TreeNode* tree, User& user, TreeNode* ret_node)
{
	if (tree == nullptr)
	{
		return;
	}
	else if (user < tree->user)
	{
		RetrieveNodeOfUser(tree->left, user, ret_node);
	}
	else if (user > tree->user)
	{
		RetrieveNodeOfUser(tree->right, user, ret_node);
	}
	else
	{
		user = *tree->user;
		ret_node = tree;
	}
}

// it is assumed that outfile is already opened from wherever it is called from
void TreeType::PreOrderPrint(TreeNode* node, std::ofstream& outfile)
{
	if (node == nullptr)
	{
		return;
	}
	node->user->Display();
	node->user->Display(outfile);
	// traverse the left subtree
	PreOrderPrint(node->left, outfile);
	// traverse the right subtree
	PreOrderPrint(node->right, outfile);
}
// it is assumed that outfile is already opened from wherever it is called from
void TreeType::PostOrderPrint(TreeNode* node, std::ofstream& outfile)
{
	if (node == nullptr)
	{
		return;
	}
	// traverse the left subtree
	PostOrderPrint(node->left, outfile);
	// traverse the right tree
	PostOrderPrint(node->right, outfile);
	// print out the first and last name
	node->user->Display();
	node->user->Display(outfile);
}
// it is assumed that outfile is already opened from wherever it is called from
void TreeType::InOrderPrint(TreeNode* node, std::ofstream &outfile)
{
	if (node == nullptr)
	{
		return;
	}
	// traverse the left subtree
	InOrderPrint(node->left, outfile);
	// print out the first and last name
	node->user->Display();
	node->user->Display(outfile);
	// traverse the right subtree
	InOrderPrint(node->right, outfile);
}

void TreeType::PurgeTree()
{
	PurgeNode(root);
}

void TreeType::PurgeNode(TreeNode* node)
{
	if (node == nullptr)
	{
		return;
	}
	PurgeNode(node->right);
	PurgeNode(node->left);
	delete node;
}
