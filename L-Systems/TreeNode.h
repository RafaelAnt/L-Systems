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
#define TREE_NODE_MAX_LENGTH_REACHED 304
#define TREE_NODE_MAX_WIDTH_REACHED 305

class TreeNode {
	char type;
	float width;
	float length;
	int stage;
	list<TreeNode*> nodes;
	TreeNode *father;
	float color[3];
	double created;
	float angle;

public:
	TreeNode();
	TreeNode(char type, TreeNode* father);
	TreeNode(char type, TreeNode* father, float angle);
	TreeNode(char type, TreeNode* father, float angle, int stage);
	TreeNode(const TreeNode & node);

	char getType();
	float getWidth();
	int setWidth(float newWidth);
	float getLength();
	int setLength(float newLength);
	int getStage();
	int setStage(int newStage);
	double getCreated();
	int setCreated(double time);
	float getAngle();
	void setAngle(float newAngle);
	list<TreeNode*> getNodes();
	void addNode(TreeNode* node);
	TreeNode* getFather();
	int setFather(TreeNode *newFather);

	int grow(list<ProductionRule> prodRule, float angleChange);
	string getLSystem();
	int incrementLength(float ratio);
	int incrementWidth(float ratio);

};