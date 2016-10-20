#include <iostream>
#include <stdio.h>

#include "Parser.h"

int main() {
	
	Parser parser = Parser();
	list<ProductionRule> pr;
	list<ProductionRule>::iterator it;
	int r = -1;
	
	if (parser.setFile("grammar.txt") == PARSER_FILE_NOT_FOUND) return -1;
	
	r=parser.parse();
	switch (r){
	case(PARSER_DONE):
		printf("AXIOMA: %s\n", parser.getAxiom());
		printf("GRAU: %f\n", parser.getDegree());
		pr = parser.getProductionRules();

		for (it = pr.begin(); it != pr.end(); it++) {
			ProductionRule aux = *it;
			printf("PRODUTION RULE:\n\tTarget: %c\n\tResult: %s\n", aux.getTarget(), aux.getResult());
		}
		break;

	case(PARSER_AXIOM_INVALID_CHARACTERS):
		printf("ERROR ON AXIOM\n");
		break;

	case(PARSER_DEGREE_INVALID_CHARACTERS):
		printf("ERROR ON DEGREE\n");
		break;

	case(PARSER_PRODUCTION_RULE_INVALID_CHARACTERS):
		printf("ERROR ON A PRODUCTION RULE\n");
		break;
		
	case(PARSER_UNKNOWN_ERROR):
		printf("UNKNOWN ERROR\n");
		break;

	default:
		printf("OTHER ERROR!!\n");
		break;
	}
	//system("pause");
	printf("\nThe End!\n");
	return 0;
}