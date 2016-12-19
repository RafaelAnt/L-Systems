#pragma once
#include <iostream>
#include <stdio.h>
#include <list>
#include <time.h>
#include <Windows.h>

#include "ProductionRule.h"

using namespace std;

#define TREE_NODE_DONE 300
#define TREE_NODE_INVALID_VALUE 301
#define TREE_NODE_INVALID_PRODUCTION_RULE 302
#define TREE_NODE_UNDIFINED_SYMBOL 303


class TreeNode {
	char type;
	float width;
	float length;
	/*float maxLength;
	float maxWidth;*/
	int stage;
	list<TreeNode*> nodes;
	TreeNode *father;
	float color[3];
	double created;

public:
	TreeNode();
	TreeNode(char type, TreeNode* father);
	TreeNode(char type, TreeNode* father, int stage);
	TreeNode(const TreeNode & node);

	char getType();
	float getWidth();
	int setWidth(float newWidth);
	float getLength();
	int setLength(float newLength);
	/*float getMaxWidth();
	int seMaxtWidth(float newWidth);
	float getMaxLength();
	int setMaxLength(float newLength);*/
	int getStage();
	int setStage(int newStage);
	double getCreated();
	int setCreated(double time);
	/*float getAngle();
	void setAngle(float newAngle);*/
	list<TreeNode*> getNodes();
	void addNode(TreeNode* node);
	TreeNode* getFather();
	int setFather(TreeNode *newFather);

	int grow(list<ProductionRule> prodRule);
	string getLSystem();
	/*int incrementLength(float ratio);
	int incrementWidth(float ratio);*/
	int getBranchNumber();

};