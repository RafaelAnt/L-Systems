#include <iostream>
#include <stdio.h>
#include <GL/glut.h>
#include <Windows.h>
#include <vector>
#include <time.h>

#include "Parser.h"
#include "TreeNode.h"
#include "Tree.h"

#define PI 3.1415
#define EXPANSIONS_NUMBER 1

using namespace std;

double lastTime = 0, elapsedTime = 0, lastElapsedTime = 0;

float degree = 0;

//Camera Variables
float eyeX = 0;
float eyeY = 0;
float eyeZ = 0;
float lookX = 0;
float lookY = 10;
float lookZ = 0;
float alpha = 0;
float beta = 0;
float dist = 30;

//int growNumber = 1;
//int stage=0;

string expanded;
Tree plant;

//lighting
GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat specularLight[] = { 0.2f, 0.2f, 0.2f, 0.5f };
GLfloat position[] = { -15.0f, 50.0f, -40.0f, 1.0f };
//GLfloat specReflection[] {0.8f,0.8f,0.8f,1.0f};

void display(void) {
	int result;

	// start by clearing the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float fieldOfView = 60;
	gluPerspective(fieldOfView, 1.0, 1, 2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//float axisDist = 10;

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	if (alpha > 2 * PI) alpha = 0;
	if (alpha < 0) alpha = 2 * PI;
	if (beta > PI / 2) beta = PI / 2;
	if (beta < -0.3) beta = -0.3;

	eyeX = dist * cos(beta) * sin(alpha);
	eyeY = dist * sin(beta);
	eyeZ = dist * cos(beta) * cos(alpha);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	gluLookAt(eyeX + lookX, eyeY + lookY, eyeZ + lookZ, lookX, lookY, lookZ, 0, 1, 0);
	
	//EIXOS
	/*glPushMatrix();
	glLineWidth(1);
	glBegin(GL_LINES);           
	// draw line for x axis red
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(axisDist, 0.0, 0.0);
	// draw line for y axis green
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, axisDist, 0.0);
	// draw line for Z axis blue
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, axisDist);
	glEnd();*/

	glPushMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//saves current lighting stuff
	//glPushAttrib(GL_LIGHTING_BIT); 
	// ambient reflection
	//GLfloat ambient[4] = { 0.82f, 0.41f, 0.12f }; 
	// diffuse reflection  
	//GLfloat diffuse[4] = { 0.82f, 0.41f, 0.12f };
	// set the ambient reflection for the object
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	// set the diffuse reflection for the object
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

	// Floor
	glBegin(GL_TRIANGLES);
		glColor3f(0.5, 0.1, 0.5);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-10, 0, -10);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(10, 0, 10);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(10, 0, -10);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-10, 0, 10);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(10, 0, 10);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-10, 0, -10);
	glEnd();

	glPopMatrix();
	//glPopAttrib();
	glColor3f(0, 1, 0);

	// Tree
	result = plant.draw();
	if (result != TREE_DONE && result != TREE_NOT_ENOUGH_POINTS_FOR_CATMULLROM) {
		printf("Fatal Error: %d\n", result);
		exit(0);
	}
	

	glutSwapBuffers();
	glutPostRedisplay();
}

void animate() {

	if (lastTime == 0) lastTime = timeGetTime();
	elapsedTime = timeGetTime() - lastTime;

	int r = plant.animate(elapsedTime);

	if (r != TREE_DONE && r != TREE_NOT_ENOUGH_POINTS_FOR_CATMULLROM) {
		printf("Fatal Error: %d\n", r);
		exit(0);
	}

	glutPostRedisplay();

}

void keyboard(unsigned char key, int x, int y){
	switch (key) {
	case 'q':			// q - Exit the program
		printf("\nThe End!\n");
		exit(0);
		break;

	case 'w':
		dist--;
		if (dist <= 0) {
			dist = 1;
		}
		break;

	case 'a':
		/*if (camAng <= 0) camAng = 360;
		else camAng--;
		eyeX = 20 * sin(camAng*PI / 180);
		eyeZ = 20 * cos(camAng*PI / 180);*/
		break;

	case 's':
		dist++;

		break;

	case 'd':
		/*if (camAng >= 360) camAng = 1;
		else camAng++;
		eyeX = 20 * sin(camAng*PI / 180);
		eyeZ = 20 * cos(camAng*PI / 180);*/
		break;

	case '+':
		lookY += 1;
		break;

	case '-':
		lookY -= 1;
		break;

	case 'r':
		printf("Restarting Animation...\n");
		plant.reset();
		break;

	case'g':
		printf("Increasing growth...\n");
		plant.reset();
		plant.grow(1);
		printf("New L-System:\n%s\n\n", plant.getLSystem().data());
		break;

	default:
		break;
	}
}

float mouseX = 0;
float mouseY = 0;

void mouseMotion(int x, int y) {
	float Xfinal = x - mouseX;
	float Yfinal = y - mouseY;

	//printf("X: %f, Y: %f \n",Xfinal,Yfinal);

	alpha = alpha + 0.005 * Xfinal;
	beta = beta - 0.005 * Yfinal;

	mouseX = x;
	mouseY = y;

	glutPostRedisplay();
}

void mouse(int botão, int estado, int x, int y) {
	if (botão == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
		mouseX = x;
		mouseY = y;
	}
}

void glutMain(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("L-Systems");

	// Use depth buffering for hidden surface elimination.
	glEnable(GL_DEPTH_TEST);

	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t%-20s %s\n", "Graphics Vendor:", glGetString(GL_VENDOR));
	printf("\t%-20s %s\n", "Renderer:", glGetString(GL_RENDERER));
	printf("\t%-20s %s\n", "Version:", glGetString(GL_VERSION));
	//printf("\t%-20s %s\n", "GLSL:", glGetString(GL_SHADING_LANGUAGE_VERSION));
	

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(animate);

	// Mouse Functions
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouse);

	// alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_LIGHT0);


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glutMainLoop();
}

int main(int argc, char** argv) {
	


	Parser parser = Parser();
	list<ProductionRule> pr;
	
	int r = -1;
	
	if (parser.setFile("grammar.txt") == PARSER_FILE_NOT_FOUND) {
		printf("File Not Found!\n");
		return -1;
	}
	
	r=parser.parse();
	switch (r){
	case(PARSER_DONE):
		parser.printGrammar();
		break;

	case(PARSER_AXIOM_INVALID_CHARACTERS):
		printf("Axiom contains invalid characters!\n");
		return -1;

	case(PARSER_DEGREE_INVALID_CHARACTERS):
		printf("Degree contains invalid characters!\n");
		return -1;

	case(PARSER_PRODUCTION_RULE_INVALID_CHARACTERS):
		printf("One of the production rules contains invalid characters!\n");
		return -1;

	case(PARSER_SYNTAX_ERROR):
		printf("Syntax error (probably some tag \"#\" out of place or missing)...\n");
		return -1;

	case(PARSER_UNKNOWN_ERROR):
		printf("UNKNOWN ERROR (probably some tag \"#\" out of place or missing)...\n");
		return -1;

	case(PARSER_PRODUCTION_RULE_EQUALS_ERROR):
		printf("One of the production rules has an invalid number of equals \"=\", only one is allowed!\n");
		return -1;

	case(PARSER_PRODUCTION_RULE_MORE_THAN_1_LEFT):
		printf("One of the production rules has more than one symbol before \"=\"!\n");
		return -1;

	default:
		printf("Unexpected error!\n");
		return -1;
	}

	degree = parser.getDegree();

	//			 Axiom					production Rules,				maxLenght,	 maxWidth,	lenght rate,	width rate,		degree rate,	maxDegree; 
	plant = Tree(parser.getAxiom(),		parser.getProductionRules(),	1.1,		 0.25,		0.01,			0.0001,			0.07,			degree		);
	
	r = plant.grow(EXPANSIONS_NUMBER);
	if (r != TREE_DONE) {
		switch (r){
		case (TREE_NODE_INVALID_PRODUCTION_RULE):
			printf("TREE_NODE_INVALID_PRODUCTION_RULE!!!!\n");
			break;
		case (TREE_NODE_UNDIFINED_SYMBOL):
			printf("TREE_NODE_UNDIFINED_SYMBOL!!!!\n");
			break;
		default:
			printf("ERRO A CRESCER!!!!\n");
			break;
		}
	}

	string aux = plant.getLSystem();
	printf("\nLSystem: \"%s\"\n", aux.data());

	

	glutMain(argc, argv);
	
	return 0;
}