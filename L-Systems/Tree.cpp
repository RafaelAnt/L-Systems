#include "Tree.h"

Tree::Tree(){
	//printf("Usei o mau\n");
	start = TreeNode();
	maxLength = -1;
	maxWidth = -1;
	lengthGrowthRate = -1;
	widthGrowthRate = -1;
}

Tree::Tree(string axiom, list<ProductionRule> prods,float maxLength, float maxWidth, float lengthGrowthRate, float widthGrowthRate, float angle){
	//printf("Usei o bom\n");
	productionRules = list<ProductionRule>(prods);
	this->maxLength = maxLength;
	this->maxWidth = maxWidth;
	this->lengthGrowthRate = lengthGrowthRate;
	this->widthGrowthRate = widthGrowthRate;
	this->angle = angle;

	TreeNode *aux;

	char ch = axiom.at(0);
	start = TreeNode(ch, nullptr);

	TreeNode *last = &start;
	//printf("char do start:     \'%c\'\n", start.getType());
	for (unsigned int j = 1; j < axiom.length(); j++) {
		ch = axiom.at(j);
		aux = new TreeNode (ch, last);
		//printf("char do Treenode:     \'%c\'\n", aux.getType());
		last->addNode(aux);
		last = aux;
	}

}

TreeNode Tree::getStart(){
	return start;
}

int Tree::setStart(TreeNode start){
	//if(start==nullptr) return TREE_INVALID_VALUE;
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

int Tree::grow(int number){
	int r;
	for (int i = 0; i < number; i++) {
		r=start.grow(productionRules, angle);
		if (r != TREE_NODE_DONE) {
			return r;
		}
	}

	return TREE_DONE;
}

void drawLine(TreeNode * node) {
	glPushAttrib(GL_LIGHTING_BIT);//saves current lighting stuff

	GLfloat ambient[4] = { 0.55f, 0.27f, 0.07f };    // ambient reflection
	GLfloat specular[4] = { 0.55f, 0.27f, 0.07f };   // specular reflection
	GLfloat diffuse[4] = { 0.55f, 0.27f, 0.07f };   // diffuse reflection

													// set the ambient reflection for the object
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	// set the diffuse reflection for the object
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	// set the specular reflection for the object      
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

	glLineWidth(node->getWidth());

	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, node->getLength(), 0);
	glEnd();
	glTranslatef(0, node->getLength(), 0);
	
	glPopAttrib();
}

int Tree::draw(){
	TreeNode *current;
	list<TreeNode*> TNlist;
	list<TreeNode*>::reverse_iterator it;
	stack<TreeNode*> q;
	float degree = 0;
	int oldStage = 1;
	TreeNode *oldfather = nullptr;

	q.push(&start);

	while (!q.empty()) {

		current = q.top();
		q.pop();


		if (current->getStage() == oldStage) {
			if (current->getFather() != nullptr && current->getFather()->getNodes().size() > 1) {
				glPopMatrix();
				glPushMatrix();
			}
		}
		else {
			if (current->getStage() > oldStage) {
				//printf("Push\n");
				oldStage = current->getStage();
				glPushMatrix();
			}
			else {
				//printf("Pop\n");
				oldStage = current->getStage();
				glPopMatrix();
			}
		}

		//Rotate if needed
		if (current->getAngle() != degree) {
			glRotatef((degree - current->getAngle()), 1, 0, 0);
			glRotatef((degree - current->getAngle()), 0, 1, 0);
			glRotatef((degree - current->getAngle()), 0, 0, 1);
			degree = current->getAngle();
		}

		if (current->getLength() > 0) {
			drawLine(current);
		}
		

		if (current->getNodes().size() != 0) {
			TNlist = current->getNodes();
			for (it = TNlist.rbegin(); it != TNlist.rend(); it++) 
				q.push(*it);
		}

	}

	while (oldStage > 1) {
		glPopMatrix();
		oldStage--;
	}

	//printf("\n\n\n");

	return TREE_DONE;
}

string Tree::getLSystem(){
	return start.getLSystem();
}

void Tree::teste(){
	printf("\n\n\nTESTE\n\nNumero de filhos:\n");

	
	TreeNode* aux = &start;
	list<TreeNode*> qq;
	int s;

	while (true){
		
		//printf("1 passo: %c\n", aux->getType());
		qq = aux->getNodes();
		//printf("Passei o 2 passo\n");
		s = qq.size();
			
		printf("\t%d\n", s);

		if (s == 0) {
			break;
		}
		else {
			//printf("Aux antes:  %x\n", aux);
			aux = *aux->getNodes().begin();
			//if (aux == nullptr) 
			//printf("Aux:  %x\n",aux);
		}
	}
	

}

int Tree::animate(double time){
	TreeNode *current;
	list<TreeNode*> TNlist;
	list<TreeNode*>::reverse_iterator it;
	stack<TreeNode*> q;

	q.push(&start);

	while (!q.empty()) {
		current = q.top();
		q.pop();

		current->incrementLength(this->lengthGrowthRate);
		current->incrementWidth(this->widthGrowthRate);

		if(current->getLength()>0.5){
			if (current->getNodes().size() != 0) {
				TNlist = current->getNodes();
				for (it = TNlist.rbegin(); it != TNlist.rend(); it++)
					q.push(*it);
			}
		}
		
	}

	return TREE_DONE;
}

int Tree::reset(){
	TreeNode *current;
	list<TreeNode*> TNlist;
	list<TreeNode*>::iterator it;
	stack<TreeNode*> q;

	q.push(&start);

	while (!q.empty()) {
		current = q.top();
		q.pop();

		current->setLength(0);
		current->setWidth(1);

		if (current->getNodes().size() != 0) {
			TNlist = current->getNodes();
			for (it = TNlist.begin(); it != TNlist.end(); it++)
				q.push(*it);
		}
	}

	return TREE_DONE;
}

