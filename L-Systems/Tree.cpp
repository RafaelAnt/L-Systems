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
	start = TreeNode(ch,nullptr);
	TreeNode last = start;

	for (int j = 1; j < axiom.length(); j++) {
		ch = axiom.at(j);
		TreeNode aux = TreeNode(ch, &last);
		last.addNode(aux);
		last = aux;
	}
	
}

TreeNode* Tree::getStart(){
	return start;
}

int Tree::setStart(TreeNode* start){
	if(start==nullptr) return TREE_INVALID_VALUE;
	this->start = start;
	return TREE_DONE;
}

float Tree::getMaxLength(){
	return maxLength;
}

int Tree::setMaxLength(float length){
	if (length <= 0) return TREE_INVALID_VALUE;
	this->maxLength = length;
	return TREE_DONE;
}

float Tree::getMaxWidth(){
	return maxWidth;
}

int Tree::setMaxWidth(float width){
	if (width <= 0) return TREE_INVALID_VALUE;
	this->maxWidth = width;
	return TREE_DONE;
}

float Tree::getLenghGrowthRate(){
	return lengthGrowthRate;
}

int Tree::setLengthGrowthRate(float rate){
	if (rate <= 0) return TREE_INVALID_VALUE;
	this->lengthGrowthRate = rate;
	return TREE_DONE;
}

float Tree::getWidthGrowthRate(){
	return widthGrowthRate;
}

int Tree::setWidthGrowthRate(float rate){
	if (rate <= 0) return TREE_INVALID_VALUE;
	this->widthGrowthRate = rate;
	return TREE_DONE;
}

