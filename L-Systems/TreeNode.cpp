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

TreeNode::TreeNode(char type, TreeNode * father, float angle){
	this->type = type;
	width = 1;
	length = 0;
	stage = 1;
	nodes = list<TreeNode>();
	color[0] = 0;
	color[1] = 1;
	color[3] = 0;
	created = clock();
	this->angle = angle;
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

int TreeNode::grow(list<ProductionRule> prodRule, float angleChange){
	list<ProductionRule>::iterator it;
	list<TreeNode>::iterator tnIt;
	string::iterator sIt;
	list<TreeNode> old;
	string result;
	TreeNode aux;
	TreeNode aux2;
	TreeNode* current = this;
	TreeNode* goBackTo = this;
	float angleMod = angle;

	printf("Growing %c...\n", type);

	if (!this->nodes.empty()) {
		printf("\tSaving old nodes...\n");
		old = list<TreeNode> (this->nodes);
		this->nodes.clear();
	}

	printf("\tFinding Production Rule...\n");
	for (it = prodRule.begin(); it != prodRule.end(); it++) {
		ProductionRule aux = *it;
		if (aux.getTarget() == this->type) {
			result = aux.getResult();
		}
	}

	if (result.size() == 0) {
		return TREE_NODE_INVALID_PRODUCTION_RULE;
	}
	else {
		printf("\tFound.\n");
	}
	
	if (result.at(0) != this->type) {
		printf("\tChanging my type to %c...\n", type);
		this->type = result.at(0);
	}

	printf("\tGrowth started...\n");
	for (sIt = result.begin() + 1; sIt != result.end(); sIt++) {
		char c = *sIt;
		switch (c){
		case 'F':
			
			aux = TreeNode ('F', current, angleMod);
			current->addNode(aux);
			aux2 = *current->getNodes().begin(); // é o aux1
			printf("\t\tF\t\tAdicionado novo F ao current: angulo: %f, angulo atravez do current: %f \n", aux.getAngle(), aux2.getAngle());
			current = &aux;
			break;

		case '+':
			
			angleMod += angleChange;
			printf("\t\t+\t\tNew Angle: %f\n",angleMod);
			break;

		case '-':
			angleMod -= angleChange;
			printf("\t\t-\t\tNew Angle: %f\n", angleMod);
			break;
			
		case '[':
			printf("\t\t[\n");
			goBackTo = current;
			break;

		case ']':
			printf("\t\t]\n");
			current = goBackTo;
			break;

		default:
			return TREE_NODE_UNDIFINED_SYMBOL;
		}
	}

	printf("\tLoading old nodes...\n");
	for (tnIt = old.begin(); tnIt != old.end(); tnIt++) {
		aux = *tnIt;
		aux.setAngle(aux.getAngle() + angleMod);
		aux.grow(prodRule, angleChange);
		current->addNode(aux);
	}
	//printf("\tComplete...\n");
	

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
		r += '[';
		for (it = nodes.begin(); it != nodes.end(); it++) {
			TreeNode aux = *it;
			r += aux.getLSystem();
		}
		r += ']';
	}

	return r;
}

