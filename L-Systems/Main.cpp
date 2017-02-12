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
#define EXPANSIONS_NUMBER 3

using namespace std;

double lastTime = 0, elapsedTime = 0, lastElapsedTime = 0;

float degree = 0;

float eyeX = 30;
float eyeY = 30;
float eyeZ = 0;
float lookX = 0;
float lookY = 10;
float lookZ = 0;
float camAng = 0;

//int growNumber = 1;
//int stage=0;

string expanded;
Tree plant;


/*int getTotalLines() {
	int r=0;
	for (int i = 0; i < EXPANSIONS_NUMBER; i++) {
		r += linesNumber[i];
	}
	return r;
}*/


void display(void) {
	// start by clearing the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float fieldOfView = 60;
	gluPerspective(fieldOfView, 1.0, 1, 2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//float axisDist = 10;


	gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, 0, 1, 0);
	
	//glPushMatrix();
	//EIXOS
	//glLineWidth(1);
	/*glBegin(GL_LINES);           
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
	glPushAttrib(GL_LIGHTING_BIT); 
	// ambient reflection
	GLfloat ambient[4] = { 0.82f, 0.41f, 0.12f }; 
	// diffuse reflection  
	GLfloat diffuse[4] = { 0.82f, 0.41f, 0.12f };
	// set the ambient reflection for the object
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	// set the diffuse reflection for the object
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

	// Floor
	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0, 0);
		glVertex3f(-10, 0, -10);
		glVertex3f(10, 0, -10);
		glVertex3f(10, 0, 10);
		glVertex3f(-10, 0, 10);
		glVertex3f(-10, 0, -10);
		glVertex3f(10, 0, 10);
	glEnd();

	glPopMatrix();
	glPopAttrib();
	glColor3f(0, 1, 0);

	// Tree
	if (plant.draw() != TREE_DONE) {
		printf("Fatal Error!\n");
		exit(0);
	}
	

	glutSwapBuffers();
	glutPostRedisplay();
}

void animate() {
	if (lastTime == 0) lastTime = timeGetTime();
		
	elapsedTime = timeGetTime() - lastTime;

	// TODO: Change the angle to make it blow in the wind

	if (plant.animate(elapsedTime) != TREE_DONE) {
		printf("Fatal Error!\n");
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
		eyeY += 1;
		break;

	case 'a':
		if (camAng <= 0) camAng = 360;
		else camAng--;
		eyeX = 20 * sin(camAng*PI / 180);
		eyeZ = 20 * cos(camAng*PI / 180);
		break;

	case 's':
		eyeY -= 1;
		break;

	case 'd':
		if (camAng >= 360) camAng = 1;
		else camAng++;
		eyeX = 20 * sin(camAng*PI / 180);
		eyeZ = 20 * cos(camAng*PI / 180);
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

	//				Axioma			prod Rules,				maxLenght, maxWidth, lenght rate, width rate, angulo; 
	plant = Tree(parser.getAxiom(), parser.getProductionRules(), 1.3, 0.4, 0.01, 0.0005, degree);
	
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