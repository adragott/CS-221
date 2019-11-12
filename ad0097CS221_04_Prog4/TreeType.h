#ifndef _TREETYPE_H_
#define _TREETYPE_H_

#pragma once
#include "homework.h"
#include <fstream>
#include "User.h"
#include "Type.h"

enum OrderType
{
	PREORDER,
	INORDER,
	POSTORDER
};

struct TreeNode
{
	TreeNode()
	{
		user = new User;
		left = nullptr;
		right = nullptr;
	}
	TreeNode(User &new_user)
	{
		user = new User(new_user);
		left = nullptr;
		right = nullptr;
	}
	~TreeNode() 
	{ 
		delete user; 
	}
	User* user;
	TreeNode* left;
	TreeNode* right;
};


class TreeType
{
public:
	
	TreeType();
	~TreeType();
	void PutUser(User* user);
	void Insert(TreeNode*& tree, User* user);
	User* GetYoungestStudent(DateType& bdate);

	// entry point into recursive print
	void Print(OrderType otype, std::ofstream &outfile);
	void Print(OrderType otype, const char* output_file_name);
	int GetLength() const;
	// find the user in the tree and then find the descendants of the user
	void PrintDescendants(User* user, OrderType otype, std::ofstream& outfile);
	void PrintDescendants(User* user, OrderType otype, const char* output_file_name);
	bool IsFull() const;
	bool IsEmpty() const;
	User* GetUser(User &user, bool& found);

private:
	TreeNode* root;
	// Recursive call used by GetLength to count the nodes on the tree
	int CountNodes(TreeNode* tree) const;
	// Recursive call to search the tree for a user
	// returns the node of the user if found, nullptr if not found
	void RetrieveNodeOfUser(TreeNode* tree, User& user, TreeNode* ret_node);
	// Recursive calls for different methods of traversing the tree to print the tree
	void PreOrderPrint(TreeNode* node, std::ofstream& outfile);
	void PostOrderPrint(TreeNode* node, std::ofstream& outfile);
	void InOrderPrint(TreeNode* node, std::ofstream& outfile);
	TreeNode* RetrieveNodeOfYoungestUser(TreeNode* node, DateType &bdate, TreeNode* ret_node);

	// functions for purging allocated memory
	void PurgeTree();
	void PurgeNode(TreeNode* node);
};

#endif