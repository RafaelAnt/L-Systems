#include <iostream>
#include <stdio.h>
#include <GL/glut.h>
#include <Windows.h>
#include <vector>
#include <time.h>

#include "Parser.h"

#define PI 3.1415
#define EXPANSIONS_NUMBER 5

using namespace std;

double lastTime = 0, elapsedTime = 0, lastElapsedTime = 0;

float lineWidth = 6;
float angle = 0;
float degree = 0;
float depth = 0;
float length = 0.001;


float eyeX = 10;
float eyeY = 50;
float eyeZ = 10;
float lookX = 0;
float lookY = 0;
float lookZ = 0;

vector<string> *stages = new vector<string>();

void push() {
	glPushMatrix();
	if (lineWidth > 0)
		lineWidth -= 1;
}

void pop() {
	glPopMatrix();
	lineWidth += 1;
}

void rotL() {
	glRotatef(degree, 1, 0, 0);
	//glRotatef(degree * 4, 0, 1, 0);
	glRotatef(degree, 0, 0, 1);
}

void rotR() {
	glRotatef(-degree, 1, 0, 0);
	//glRotatef(degree * 4, 0, 1, 0);
	glRotatef(-degree, 0, 0, 1);
}

void drawLine() {
	glPushAttrib(GL_LIGHTING_BIT);//saves current lighting stuff


								  //glColor3f(0.55, 0.27, 0.07);
	GLfloat ambient[4] = { 0.55, 0.27, 0.07 };    // ambient reflection
	GLfloat specular[4] = { 0.55, 0.27, 0.07 };   // specular reflection
	GLfloat diffuse[4] = { 0.55, 0.27, 0.07 };   // diffuse reflection


												 // set the ambient reflection for the object
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	// set the diffuse reflection for the object
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	// set the specular reflection for the object      
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glLineWidth(lineWidth);

	glBegin(GL_LINES);

	glVertex3f(0, 0, 0);
	glVertex3f(0, length, 0);
	glEnd();

	glTranslatef(0, length, 0);
	glPopAttrib();
}


void draw() {
	char ch;
	string LSystem = stages->at(depth);
	for (int i = 0; i < LSystem.length(); i++) {
		ch = LSystem.at(i);

		switch (ch) {
		case '[':
			push();
			break;

		case ']':
			pop();
			break;

		case '+':
			rotR();
			break;

		case '-':
			rotL();
			break;

		case 'F':
			drawLine();
			break;

		default: //other
			break;
		}
	}
}

void display(void) {
	// start by clearing the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float fieldOfView = 60;
	gluPerspective(fieldOfView, 1.0, 1, 2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float axisDist = 10;


	gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, 0, 1, 0);
	

	glPushMatrix();

	//EIXOS
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
	glEnd();

	glColor3f(1.0, 0.75, 0.3);
	glutSolidCube(1);
	glColor3f(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPushAttrib(GL_LIGHTING_BIT); //saves current lighting stuff
	GLfloat ambient[4] = { 0.82, 0.41, 0.12 };    // ambient reflection
	GLfloat diffuse[4] = { 0.82, 0.41, 0.12 };   // diffuse reflection    
												 // set the ambient reflection for the object
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	// set the diffuse reflection for the object
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

	//glColor3f(1.0, 0, 0);
	glBegin(GL_TRIANGLES);
	//glColor3f(1.0, 0, 0);
	glVertex3f(-20, 0, -20);
	glVertex3f(20, 0, -20);
	glVertex3f(20, 0, 20);
	glVertex3f(-20, 0, 20);
	glVertex3f(-20, 0, -20);
	glVertex3f(20, 0, 20);
	glEnd();

	glPopMatrix();
	glPopAttrib();

	//draw();
	glutSwapBuffers();
	glutPostRedisplay();
}

void animate() {
	if (lastTime == 0)
		lastTime = timeGetTime();

	elapsedTime = timeGetTime() - lastTime;

	// Change the angle to make it blow in the wind
	/*float numR = (float)rand() / RAND_MAX;


	if (ANGLE > 21.5) {
		if (numR < 0.5) {
			incr = -0.15;
		}
		else {
			incr = -0.1;
		}
	}
	else if (ANGLE < 18.5) {
		if (numR > 0.5) {
			incr = 0.15;
		}
		else {
			incr = 0.1;
		}
	}
	ANGLE += incr;*/

	if (depth < EXPANSIONS_NUMBER)
		length += 0.001;

	if (elapsedTime - lastElapsedTime > 2000 && depth < EXPANSIONS_NUMBER) {
		depth++;
		lastElapsedTime = elapsedTime;
		cout << "a ";

	}

	elapsedTime = elapsedTime / 5000;
	//float t = (sin((elapsedTime*PI - PI / 2)) + 1) / 2;
	//float p = (1 - t)*STARTX + t*ENDX;

	//if (cam) eyeX = p;
	glutPostRedisplay();

}

void keyboard(unsigned char key, int x, int y){
	switch (key) {
	case 'q':			// q - Exit the program
		exit(0);
		break;

	case 'w':
		eyeZ += 1;
		break;

	case 'a':
		eyeX -= 1;
		break;

	case 's':
		eyeZ -= 1;
		break;

	case 'd':
		eyeX += 1;
		break;

	case '+':
		eyeY += 1;
		break;

	case '-':
		eyeY -= 1;
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

	string expanded;
	stages = new vector<string>();
	for (int i = 0; i < EXPANSIONS_NUMBER; i++) {
		expanded = parser.expand(i);
		stages->push_back(expanded);
		//printf("Expanded %d times resulted in:\n%s\n\n\n", i, stages->at(i).data());
		
	}

	
	

	glutMain(argc, argv);

	//system("pause");
	printf("\nThe End!\n");
	return 0;
}