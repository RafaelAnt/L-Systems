#include <iostream>
#include <stdio.h>
#include <GL/glut.h>
#include <Windows.h>

#include "Parser.h"

#define PI 3.1415
#define EXPANSIONS_NUMBER 3

using namespace std;

void glutMain() {
	glutInit(nullptr,nullptr);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("L-Systems");

	// Use depth buffering for hidden surface elimination.
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(animate);
	trees = new vector<string>();
	for (int i = 0; i <= DEPTH; i++) {
		expand(num);
	}
	glutMainLoop();
}

int main() {
	
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


	string expanded = parser.expand(EXPANSIONS_NUMBER);
	printf("Expanded %d times resulted in:\n%s\n", EXPANSIONS_NUMBER, expanded.data());

	glutMain();

	//system("pause");
	printf("\nThe End!\n");
	return 0;
}