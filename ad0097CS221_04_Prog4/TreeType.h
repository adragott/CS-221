#ifndef _TREETYPE_H_
#define _TREETYPE_H_

#pragma once
#include "homework.h"
#include "User.h"
#include "Type.h"

enum OrderType
{
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
};

struct TreeNode
{
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
	void Insert(TreeNode* tree, User &user);
	User* GetYoungestStudent(DateType& bdate);
	void Print(OrderType otype, std::ofstream &outfile);
	void PrintTree(TreeNode tree, std::ofstream& outfile);
	int GetLength() const;
	// find the user in the tree and then find the descendants of the user
	void PrintDescendants(User* user, OrderType otype, std::ofstream& outfile);
	bool IsFull() const;
	bool IsEmpty() const;
	User* GetUser(User user, bool& found);

private:
	TreeNode* root;
	// Recursive call used by GetLength to count the nodes on the tree
	int CountNodes(TreeNode* tree);
	// Recursive call used by GetItem to search the tree for an item
	void Retrieve(TreeNode* tree, User &user, bool &found);

};

#endif