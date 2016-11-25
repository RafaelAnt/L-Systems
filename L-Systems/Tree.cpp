#include <iostream>
#include <stdio.h>

#include "Tree.h"

Tree::Tree(string axiom, list<ProductionRule> prods,float maxLength, float maxWidth, float lengthGrowthRate, float widthGrowthRate){
	productionRules = list<ProductionRule>(prods);
	this->maxLength = maxLength;
	this->maxWidth = maxWidth;
	this->lengthGrowthRate = lengthGrowthRate;
	this->widthGrowthRate = widthGrowthRate;


	char ch = axiom.at(0);
	start = TreeNode(ch);
	TreeNode last = start;

	for (int j = 1; j < axiom.length(); j++) {
		ch = axiom.at(j);
		TreeNode aux = TreeNode(ch);
		last.addNode(aux);
		last = aux;
	}
	
}
