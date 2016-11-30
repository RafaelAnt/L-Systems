#pragma once
#include <iostream>
#include <stdio.h>
#include <list>
#include <time.h>


using namespace std;

#define TREE_NODE_DONE 300
#define TREE_NODE_INVALID_VALUE 301

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
	TreeNode(char type, TreeNode* father);
	TreeNode(const TreeNode& node);

	char getType();
	float getWidth();
	int setWidth(float newWidth);
	float getLength();
	int setLength(float newLength);
	int getStage();
	int setStage(int newStage);
	clock_t getCreated();
	float getAngle();
	void setAngle(float newAngle);
	list<TreeNode> getNodes();
	void addNode(TreeNode node);
	TreeNode* getFather();
	int setFather(TreeNode *newFather);

	int branch(char ch);
	int grow(string prodRule);
	string getLSystem();

};