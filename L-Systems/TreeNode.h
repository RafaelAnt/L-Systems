#pragma once
#include <iostream>
#include <list>
#include <time.h>
//#include <boost/any.hpp>

using namespace std;

#define TREE_BRANCH_DONE 300
#define TREE_BRANCH_INVALID_VALUE 301

class TreeNode {
	char type;
	float width;
	float length;
	int stage;
	list<TreeNode> nodes;
	TreeNode *father;
	float color[3];
	clock_t created;
	float angle;

public:
	TreeNode();
	TreeNode(char type);
	TreeNode(const TreeNode& node);

	char getType();
	float getWidth();
	int setWidth(float newWidth);
	float getLength();
	int setLength(float newLength);
	int getStage();
	int setStage();
	clock_t getCreated();
	float getAngle();
	void setAngle(float angle);
	list<TreeNode> getNodes();
	void addNode(TreeNode node);

	int grow(string prodRule);

};