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
private:
	User* user;
	TreeNode* left;
	TreeNode* right;
};


class TreeType
{
public:
	TreeType();
	~TreeType();
	void PutUser(User user);
	void Insert(TreeNode* tree, ItemType item);
	User* GetYoungestStudent(DateType& bdate);
	void Print(OrderType otype, std::ofstream &outfile);
	void PrintTree(TreeNode tree, std::ofstream& outfile);
	// find the user in the tree and then find the descendants of the user
	void PrintDescendants(User* user, OrderType otype, std::ofstream& outfile);
	bool IsFull() const;
	bool IsEmpty() const;

private:
	TreeNode* root;

};

#endif