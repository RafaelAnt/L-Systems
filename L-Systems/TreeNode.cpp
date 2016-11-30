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
	father = nullptr;
}

TreeNode::TreeNode(char type, TreeNode* father){
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
	this->father = father;
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
	this->father = node.father;
}

char TreeNode::getType(){
	return type;
}

float TreeNode::getWidth(){
	return width;
}

int TreeNode::setWidth(float newWidth){
	if (newWidth <= 0) {
		return TREE_NODE_INVALID_VALUE;
	}
	width = newWidth;
	return TREE_NODE_DONE;
}

float TreeNode::getLength(){
	return length;
}

int TreeNode::setLength(float newLength){
	if (newLength <= 0) {
		return TREE_NODE_INVALID_VALUE;
	}
	length = newLength;
	return TREE_NODE_DONE;
}

int TreeNode::getStage(){
	return stage;
}

int TreeNode::setStage(int newStage){
	if (newStage < 0) {
		return TREE_NODE_INVALID_VALUE;
	}
	stage = newStage;
	return TREE_NODE_DONE;
}

clock_t TreeNode::getCreated(){
	return created;
}

float TreeNode::getAngle(){
	return angle;
}

void TreeNode::setAngle(float newAngle){
	angle = newAngle;
}

list<TreeNode> TreeNode::getNodes(){
	return list<TreeNode>(nodes);
}

void TreeNode::addNode(TreeNode node){
	nodes.push_back(node);
}

TreeNode * TreeNode::getFather(){
	return father;
}

int TreeNode::setFather(TreeNode * newFather){
	if (newFather = nullptr) return TREE_NODE_INVALID_VALUE;
	this->father = newFather;
	return TREE_NODE_DONE;
}

string TreeNode::getLSystem(){
	//printf("teste\n");
	list<TreeNode>::iterator it;

	string r;
	r += type;
	if (nodes.size() == 0) {
		return r;
	}
	if (nodes.size() == 1) {
		it = nodes.begin();
		TreeNode aux = *it;
		r += aux.getLSystem();
	}
	else {
		for (it = nodes.begin(); it != nodes.end(); it++) {
			r += '[';
			TreeNode aux = *it;
			r += aux.getLSystem();
			r += ']';
		}
	}

	return r;
}

