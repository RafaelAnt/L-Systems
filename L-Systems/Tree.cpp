#include "Tree.h"

Tree::Tree(){
	//printf("Usei o mau\n");
	start = TreeNode();
	maxLength = -1;
	maxWidth = -1;
	lengthGrowthRate = -1;
	widthGrowthRate = -1;
	angleGrowthRate = -1;
}

Tree::Tree(string axiom, list<ProductionRule> prods,float maxLength, float maxWidth, float lengthGrowthRate, float widthGrowthRate, float angleGrowthRate, float angle){
	//printf("Usei o bom\n");
	productionRules = list<ProductionRule>(prods);
	this->maxLength = maxLength;
	this->maxWidth = maxWidth;
	this->lengthGrowthRate = lengthGrowthRate;
	this->widthGrowthRate = widthGrowthRate;
	this->angleGrowthRate = angleGrowthRate;
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

float Tree::getAngleGrowthRate(){
	return angleGrowthRate;
}

int Tree::setAngleGrowthRate(float rate){
	if (rate <= 0) return TREE_INVALID_VALUE;
	this->angleGrowthRate = rate;
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
		r=start.grow(productionRules);
		if (r != TREE_NODE_DONE) {
			return r;
		}
	}

	return TREE_DONE;
}

int Tree::drawLine(TreeNode * node) {
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

	glLineWidth(0.5);

	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, node->getLength(), 0);
	glEnd();
	//glTranslatef(0, node->getLength(), 0);
	
	glPopAttrib();

	return TREE_DONE;
}


int Tree::drawIntersection(TreeNode * node){
	if (node->getBranchNumber() > 1) {
		glutSolidSphere(node->getWidth(), 7, 7);
		//glutSolidSphere(0.45, 7, 7);
	}
	return TREE_DONE;
}

void Tree::rotL(TreeNode* node) {
	glRotatef(node->getDegree(), 1, 0, 0);
	glRotatef(node->getDegree(), 0, 1, 0);
	glRotatef(node->getDegree(), 0, 0, 1);
}

void Tree::rotR(TreeNode* node) {
	glRotatef(-node->getDegree(), 1, 0, 0);
	glRotatef(node->getDegree(), 0, 1, 0);
	glRotatef(-node->getDegree(), 0, 0, 1);
}

int Tree::incrementLength(TreeNode *current){
	float l = current->getLength();
	if (l >= maxLength) return TREE_MAX_LENGTH_REACHED;

	l += lengthGrowthRate / current->getStage();

	current->setLength(l);

	return TREE_DONE;
}

int Tree::incrementWidth(TreeNode *current){
	float w = current->getWidth();
	if (w >= (maxWidth - (0.05*current->getStage()))) return TREE_MAX_WIDTH_REACHED;

	w += widthGrowthRate / current->getStage();

	current->setWidth(w);
	
	return TREE_DONE;
}

int Tree::incrementDegree(TreeNode * current){
	float a = current->getDegree();
	if (a >= (angle - (0.05*current->getStage()))) return TREE_MAX_ANGLE_REACHED;

	a += angleGrowthRate / current->getStage();

	current->setDegree(a);

	return TREE_DONE;
}

int Tree::drawBranch(TreeNode * current){ //TODO: check and fix!
	
	glPushMatrix();
	//glRotatef(-90, 1, 0, 0); //rotate the cone
	//glutSolidCone(current->getWidth(), current->getLength(), 5, 5);

	glBegin(GL_TRIANGLE_STRIP);
	for (float i = 0; i < 2 * 3.14; i += 0.5) {
		//glColor3f(0.5, 0.5, 0.5);
		glNormal3f(sin(i),0.0,cos(i));
		glVertex3f(current->getWidth()*sin(i), current->getLength(), current->getWidth()*cos(i));
		glNormal3f(sin(i), 0.0, cos(i));
		glVertex3f(current->getWidth()*sin(i), 0, current->getWidth()*cos(i));
	}
	glNormal3f(sin(0), 0.0, cos(0));
	glVertex3f(current->getWidth()*sin(0.0), current->getLength(), current->getWidth()*cos(0.0));
	glNormal3f(sin(0), 0.0, cos(0));
	glVertex3f(current->getWidth()*sin(0.0), 0, current->getWidth()*cos(0.0));
	glEnd();

	glPopMatrix();
	
	return TREE_DONE;
}

int Tree::drawAux(TreeNode* node) {
	list<TreeNode*>::iterator it;
	list<TreeNode*> nodes = node->getNodes();
	TreeNode* aux;
	int r;

	//Rotate if needed
	switch (node->getType()){
	case 'F':
		if (node->getLength() > 0) {
			drawLine(node);
			drawBranch(node);
			glTranslatef(0, node->getLength(), 0);
			drawIntersection(node);
		}
		break;
	case '+':
		rotR(node);
		break;
	case '-':
		rotL(node);
		break;
	default:
		break;
	}

	if (nodes.size() == 0) {
		return TREE_DONE;
	}

	if (nodes.size() >= 1) {

		for (it = nodes.begin(); it != nodes.end(); it++) {
			aux = *it;
			if (aux->getStage() > node->getStage()) {
				glPushMatrix();
			}
			r = drawAux(aux);
			if (r != TREE_DONE) return r;
			if (aux->getStage() > node->getStage()) {
				glPopMatrix();
			}
		}
	}


	return TREE_DONE;
}


int Tree::draw(){

	int r = drawAux(&start);

	return r;
}

string Tree::getLSystem(){
	return start.getLSystem();
}

//TODO: Remove
/*void Tree::teste(){
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
	
	
}*/

int Tree::animate(double time){
	TreeNode *current;
	list<TreeNode*> TNlist;
	list<TreeNode*>::reverse_iterator it;
	stack<TreeNode*> q;

	q.push(&start);

	// TODO: Change the angle to make it blow in the wind

	while (!q.empty()) {
		current = q.top();
		q.pop();

		incrementLength(current);
		incrementWidth(current);
		incrementDegree(current);

		if(current->getLength()>0.3){
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
