#pragma once
#include <iostream>
#include <list>

#include "ProductionRule.h"
#include "TreeBranch.h"

#define TREE_DONE 200

using namespace std;



class Tree {
	list<ProductionRule> productionRules;
	TreeBranch start;

public:
	Tree(list<ProductionRule>);

};
