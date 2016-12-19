#pragma once
#include <iostream>
#include <list>
#include <stdio.h>
#include <GL/glut.h>
#include <stack> 

#include "ProductionRule.h"
#include "TreeNode.h"

#define TREE_DONE 200
#define TREE_INVALID_VALUE 201
#define TREE_MAX_LENGTH_REACHED 202
#define TREE_MAX_WIDTH_REACHED 203

#define TREE_BRANCH_POINTS 8
using namespace std;

class Tree {
	list<ProductionRule> productionRules;
	TreeNode start;
	float maxLength;
	float maxWidth;
	float lengthGrowthRate;
	float widthGrowthRate;
	float angle;

public:
	Tree();
	Tree(string axiom, list<ProductionRule> prods, float maxLength, float maxWidth, float lengthGrowthRate, float widthGrowthRate, float angle);

	TreeNode getStart();
	int setStart(TreeNode start);
	float getMaxLength();
	int setMaxLength(float length);
	float getMaxWidth();
	int setMaxWidth(float width);
	float getLenghGrowthRate();
	int setLengthGrowthRate(float rate);
	float getWidthGrowthRate();
	int setWidthGrowthRate(float rate);

	int grow(int number);
	int draw();
	string getLSystem();
	void teste();
	int animate(double time);
	int reset();


private:
	int drawAux(TreeNode* node);
	void rotL();
	void rotR();
	int incrementLength(TreeNode *current);
	int incrementWidth(TreeNode *current);
	int drawBranch(TreeNode *current);
	int drawLine(TreeNode *node);
	int drawIntersection(TreeNode* node);
};
