#include "TreeNode.h"



TreeNode::TreeNode(){
	this->type = '0';
	width = -1;
	length = -1;
	degree = 1;
	/*maxWidth = 1;
	maxLength = 1;*/
	stage = -1;
	nodes = list<TreeNode*>();
	color[0] = -1;
	color[1] = -1;
	color[3] = -1;
	created = timeGetTime();
	father = nullptr;
}

TreeNode::TreeNode(char type, TreeNode* father){
	this->type = type;
	width = 0;
	length = 0;
	degree = 1;
	/*maxWidth = 1;
	maxLength = 1;*/
	stage = 1;
	nodes = list<TreeNode*>();
	color[0] = 0;
	color[1] = 1;
	color[3] = 0;
	created = timeGetTime();
	this->father = father;
}

//UNUSED
/*TreeNode::TreeNode(char type, TreeNode * father, float angle){
	this->type = type;
	width = 1;
	length = 0;
	stage = 1;
	nodes = list<TreeNode*>();
	color[0] = 0;
	color[1] = 1;
	color[3] = 0;
	created = timeGetTime();
	this->angle = angle;
	this->father = father;
}*/


TreeNode::TreeNode(char type, TreeNode * father, int stage){
	this->type = type;
	width = 0;
	length = 0;
	degree = 1;
	/*maxWidth = 1;
	maxLength = 1;*/
	this->stage = stage;
	circlePoints = vector<Point>();
	centralPoint = Point(0, 0, 0);
	nodes = list<TreeNode*>();
	color[0] = 0;
	color[1] = 1;
	color[3] = 0;
	created = timeGetTime();
	this->father = father;

	if (type == '+' || type == '-') length = 1;
	else length = 0;
}

TreeNode::TreeNode(const TreeNode &node) {
	this->type = node.type;
	this->width = node.width;
	this->length = node.length;
	this->degree = node.degree;
	this->stage = node.stage;
	circlePoints = vector<Point>();
	centralPoint = Point(0, 0, 0);
	this->nodes = list<TreeNode*>(node.nodes);
	this->color[0] = node.color[0];
	this->color[1] = node.color[1];
	this->color[2] = node.color[2];
	this->created = node.created;
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

float TreeNode::getDegree(){
	return this->degree;
}

int TreeNode::setDegree(float newDegree){
	this->degree = newDegree;
	return TREE_NODE_DONE;
}

/*float TreeNode::getMaxWidth(){
	return maxWidth;
}

int TreeNode::seMaxtWidth(float newWidth){
	if (newWidth <= 0) return TREE_NODE_INVALID_VALUE;
	this->maxWidth = newWidth;
	return TREE_NODE_DONE;
}

float TreeNode::getMaxLength(){
	return maxLength;
}

int TreeNode::setMaxLength(float newLength){
	if (newLength <= 0) return TREE_NODE_INVALID_VALUE;
	this->maxWidth = newLength;
	return TREE_NODE_DONE;
}*/

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

double TreeNode::getCreated(){
	return created;
}

int TreeNode::setCreated(double time){
	this->created = time;
	return TREE_NODE_DONE;
}

/*float TreeNode::getAngle(){
	return angle;
}

void TreeNode::setAngle(float newAngle){
	angle = newAngle;
}*/

list<TreeNode*> TreeNode::getNodes(){
	return nodes;
}

void TreeNode::addNode(TreeNode* node){
	nodes.push_back(node);
}

Point TreeNode::getCentralPoint(){
	return this->centralPoint;
}

int TreeNode::setCentralPoint(Point p){
	//if (p == nullptr) return TREE_NODE_NULL_POINT;
	this->centralPoint = p;
	return TREE_NODE_DONE;
}

int TreeNode::setCentralPoint(float x, float y, float z){
	this->centralPoint = Point(x, y, z);
	return TREE_NODE_DONE;
}

vector<Point> TreeNode::getCirclePoints(){
	return circlePoints;
}

int TreeNode::setCirclePoints(vector<Point> points){
	this->circlePoints = points;
	return TREE_NODE_DONE;
}

TreeNode * TreeNode::getFather(){
	return father;
}

int TreeNode::setFather(TreeNode * newFather){
	if (newFather == nullptr) return TREE_NODE_INVALID_VALUE;
	this->father = newFather;
	return TREE_NODE_DONE;
}

int TreeNode::grow(list<ProductionRule> prodRule){
	list<ProductionRule>::iterator it;
	list<TreeNode*>::iterator tnIt;
	string::iterator sIt;
	list<TreeNode*> old;
	string result;
	TreeNode *aux;
	TreeNode *current = this;
	TreeNode *goBackTo = this;
	int stageMod = this->stage;

	//printf("Growing %c...\n", type);

	if (this->getType() == '+' || this->getType() == '-') {

		for (tnIt = this->nodes.begin(); tnIt != this->nodes.end(); tnIt++) {
			aux = *tnIt;
			int r = aux->grow(prodRule);
			if (r != TREE_NODE_DONE) return r;
		}
		return TREE_NODE_DONE;
	}
	else {

		if (!this->nodes.empty()) {
			//printf("\tSaving old nodes...\n");
			old = list<TreeNode*>(this->nodes);
			this->nodes.clear();
		}



		//printf("\tFinding Production Rule...\n");
		for (it = prodRule.begin(); it != prodRule.end(); it++) {
			ProductionRule aux = *it;
			if (aux.getTarget() == this->type) {
				result = aux.getResult();
				break;
			}
		}

		if (result.size() == 0) {
			return TREE_NODE_INVALID_PRODUCTION_RULE;
		}
		else {
			//printf("\tFound.\n");
		}

		if (result.at(0) != this->type) {
			//printf("\tChanging my type to %c...\n", result.at(0));
			this->type = result.at(0);
		}

		//printf("\tGrowth started...\n");
		for (sIt = result.begin() + 1; sIt != result.end(); sIt++) {
			char c = *sIt;
			switch (c) {
			case 'F':
				aux = new TreeNode('F', current, stageMod);
				current->addNode(aux);
				//printf("\t\tF\t\tAdicionado novo F ao current: angulo: %f, stage: %d\n", aux->getAngle(), stageMod);
				current = aux;
				break;

			case '+':
				aux = new TreeNode('+', current, stageMod);
				current->addNode(aux);
				current = aux;
				break;

			case '-':
				aux = new TreeNode('-', current, stageMod);
				current->addNode(aux);
				current = aux;
				break;

			case '[':
				//printf("\t\t[\n");
				goBackTo = current;
				stageMod++;
				break;

			case ']':
				//printf("\t\t]\n");
				current = goBackTo;
				stageMod--;
				break;

			default:
				return TREE_NODE_UNDIFINED_SYMBOL;
			}
		}


		//printf("\tLoading old nodes...\n");
		for (tnIt = old.begin(); tnIt != old.end(); tnIt++) {
			aux = *tnIt;
			int r = aux->grow(prodRule);
			if (r != TREE_NODE_DONE) return r;
			current->addNode(aux);
		}
		//printf("\tComplete...\n");
	}

	return TREE_NODE_DONE;
}

string TreeNode::getLSystem(){
	//printf("teste\n");
	list<TreeNode*>::iterator it;
	TreeNode* aux;
	string r;
	r += type;

	if (nodes.size() == 0) {
		//printf("0 filhos\n");
		return r;
	}

	if (nodes.size() >= 1) {

		//printf("1 ou mais filhos\n");
		
		for (it = nodes.begin(); it != nodes.end(); it++) {
			aux = *it;
			if (aux->getStage() > this->getStage()) {
				r += '[';
			}
			r += aux->getLSystem();
			if (aux->getStage() > this->getStage()) {
				r += ']';
			}
			
		}

	}
	return r;
}

int TreeNode::getBranchNumber(){
	list<TreeNode*>::iterator it;
	TreeNode* aux;

	if (this->nodes.size() == 0) return 0;

	int r = 0;

	for (it = nodes.begin(); it != nodes.end(); it++) {
		aux = *it;
		if(aux->getType()=='F')	r++;
		else r += aux->getBranchNumber();

	}

	return r;
}

int TreeNode::clearPoints(){
	this->centralPoint = { 0,0,0 };
	circlePoints.clear();
	return TREE_NODE_DONE;
}

