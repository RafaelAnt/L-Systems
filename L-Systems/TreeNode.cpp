#include <iostream>
#include <stdio.h>

#include "TreeNode.h"



TreeNode::TreeNode(){
	this->type = '0';
	width = -1;
	length = -1;
	stage = -1;
	nodes = list<TreeNode>();
	color[0] = -1;
	color[1] = -1;
	color[3] = -1;
	created = clock();
	angle = -1;
}

TreeNode::TreeNode(char type){
	this->type = type;
	width = 1;
	length = 0;
	stage = 1;
	nodes = list<TreeNode>();
	color[0] = 0;
	color[1] = 1;
	color[3] = 0;
	created = clock();
	angle = 0;
}

TreeNode::TreeNode(const TreeNode &node) {
	this->type = node.type;
	this->width = node.width;
	this->length = node.length;
	this->stage = node.stage;
	this->nodes = list<TreeNode>(node.nodes);
	this->color[0] = node.color[0];
	this->color[1] = node.color[1];
	this->color[2] = node.color[2];
	this->created = node.created;
	this->angle = node.angle;
}

float TreeNode::getWidth(){
	return width;
}

