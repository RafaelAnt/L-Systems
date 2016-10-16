#include <iostream>
#include <stdio.h>

#include "Parser.h"

int main() {
	
	Parser p = Parser();
	int r = -1;
	
	if (p.setFile("grammar.txt") == PARSER_FILE_NOT_FOUND) return -1;
	
	r=p.parse();
	switch (r){
	case(PARSER_AXIOM_INVALID_CHARACTERS):
		printf("ERROR ON AXIOM\n");
		break;

	case(PARSER_DEGREE_INVALID_CHARACTERS):
		printf("ERROR ON DEGREE\n");
		break;

	case(PARSER_PRODUCTION_RULE_INVALID_CHARACTERS):
		printf("ERROR ON A PRODUCTION RULE\n");
		break;

	default:
		break;
	}
	//system("pause");
	printf("\nThe End!\n");
	return 0;
}