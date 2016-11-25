#include <iostream>
#include <stdio.h>
#include <GL/glut.h>
#include <Windows.h>
#include <vector>
#include <time.h>

#include "Parser.h"
#include "TreeBranch.h"

#define PI 3.1415
#define EXPANSIONS_NUMBER 1

using namespace std;

double lastTime = 0, elapsedTime = 0, lastElapsedTime = 0;

float degree = 0;

float length[EXPANSIONS_NUMBER];
float lineWidth[EXPANSIONS_NUMBER];
int linesNumber[EXPANSIONS_NUMBER];
int linesToDraw[EXPANSIONS_NUMBER];
int lastDrawn[EXPANSIONS_NUMBER];


float eyeX = 50;
float eyeY = 50;
float eyeZ = 0;
float lookX = 0;
float lookY = 30;
float lookZ = 0;

int stage = 0;
int speed = 0.01;

string expanded;
//vector<string> *stages = new vector<string>();

void push() {
	stage++;
	glPushMatrix();	
}

void pop() {
	glPopMatrix();
	stage--;
}

void rotL() {
	glRotatef(degree, 1, 0, 0);
	glRotatef(degree, 0, 1, 0);
	glRotatef(degree, 0, 0, 1);
}

void rotR() {
	glRotatef(-degree, 1, 0, 0);
	glRotatef(degree, 0, 1, 0);
	glRotatef(-degree, 0, 0, 1);
}

int getTotalLines() {
	int r=0;
	for (int i = 0; i < EXPANSIONS_NUMBER; i++) {
		r += linesNumber[i];
	}
	return r;
}

void drawLine() {
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

	// Stage is the push count

	//glLineWidth(lineWidth[stage] - (linesNumber[stage] * 0.001));
	glLineWidth(1);
	
	if (linesNumber[stage] <= linesToDraw[stage] && linesNumber[stage] > lastDrawn[stage]) {
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, length[stage], 0);
		glEnd();
		glTranslatef(0, length[stage], 0);
	}
	
	if (linesNumber[stage] <= linesToDraw[stage] && linesNumber[stage] < lastDrawn[stage]) {
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);
		glEnd();
		glTranslatef(0, 1, 0);
	}
	
	/*
	if (getTotalLines() <= linesToDraw[0]) {
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);
		glEnd();
		glTranslatef(0, 1, 0);
	}
	if (getTotalLines() == linesToDraw[0]) {
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, length[0], 0);
		glEnd();
		glTranslatef(0, length[0], 0);
	}

	*/

	glPopAttrib();
}


void draw() {
	char ch;
	stage = 0;
	for (int i = 0; i < EXPANSIONS_NUMBER; i++) {
		linesNumber[i] = 0;
	}

	for (unsigned int i = 0; i < expanded.length(); i++) {
		ch = expanded.at(i);

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
			linesNumber[stage]++;
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

	//glColor3f(1.0, 0.75, 0.3);
	//glutSolidCube(1);
	//glColor3f(0, 0, 0);
	//glPopMatrix();

	glPushMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPushAttrib(GL_LIGHTING_BIT); //saves current lighting stuff
	GLfloat ambient[4] = { 0.82f, 0.41f, 0.12f };    // ambient reflection
	GLfloat diffuse[4] = { 0.82f, 0.41f, 0.12f };   // diffuse reflection    
												 // set the ambient reflection for the object
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	// set the diffuse reflection for the object
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

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
	draw();
	glutSwapBuffers();
	glutPostRedisplay();
}

void animate() {
	if (lastTime == 0)
		lastTime = timeGetTime();

	elapsedTime = timeGetTime() - lastTime;

	// TODO: Change the angle to make it blow in the wind

	/*
	if (length[0] < 1) {
		length[0] += 0.01;
		lineWidth[0] += 0.01;
	}
	else {
		//lastDrawn[0] = linesToDraw[0];
		linesToDraw[0] += 1;
		//printf("lines do draw: %d    Lines Number: %d\n", linesToDraw[0], linesNumber[0]);
		length[0] = 0.001;
	}*/
	
	if (length[0] < 1) {
		length[0] += 0.05;
		lineWidth[0] += 0.01;
	}
	else {
		lastDrawn[0] = linesToDraw[0];
		linesToDraw[0]+=1;
		//printf("lines do draw: %d    Lines Number: %d\n", linesToDraw[0], linesNumber[0]);
		length[0] = 0.001;
	}

	
	for (int i = 1; i < EXPANSIONS_NUMBER; i++) {
		if (lastDrawn[i - 1] > 10) {
			if (length[i] < 1) {
				length[i] += 0.05;
				lineWidth[i] += 0.01;
			}
			else {
				lastDrawn[i] = linesToDraw[i];
				linesToDraw[i]+= 2;
				length[i] = 0.001;
			}
		}
	}
	

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

	case 'r':
		//stage = 0;

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

	

	expanded = parser.expand(EXPANSIONS_NUMBER);
	printf("\nExpanded %d times resulted in:\n%s\n\n", EXPANSIONS_NUMBER, expanded.data());

	for (int i = 0; i < EXPANSIONS_NUMBER; i++) {
		length[i] = 0.001;
		lineWidth[i] = (float)(EXPANSIONS_NUMBER - (0.5 * i));
		linesNumber[i] = 0;
		linesToDraw[i] = 0;
		lastDrawn[i] = 0;
		//printf("for i = %d, length: %f. lineWidth = %f\n", i, length[i], lineWidth[i]);
	}
	linesToDraw[0] = 1;

	glutMain(argc, argv);

	//system("pause");
	printf("\nThe End!\n");
	return 0;
}