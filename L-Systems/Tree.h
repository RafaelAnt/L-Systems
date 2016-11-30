#pragma once
#include <iostream>
#include <list>
#include <stdio.h>

#include "ProductionRule.h"
#include "TreeNode.h"

#define TREE_DONE 200
#define TREE_INVALID_VALUE 201
using namespace std;



class Tree {
	list<ProductionRule> productionRules;
	TreeNode start;
	float maxLength;
	float maxWidth;
	float lengthGrowthRate;
	float widthGrowthRate;

public:
	Tree();
	Tree(string axiom, list<ProductionRule> prods, float maxLength, float maxWidth, float lengthGrowthRate, float widthGrowthRate);

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

	string getLSystem();
};
