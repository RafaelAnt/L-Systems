#include <iostream>
#include <stdio.h>

#include "Parser.h"

#define LINE_MAX 500
#define SAVE_TO_AXIOM 200
#define SAVE_TO_DEGREE 201
#define SAVE_TO_PRODUCTION_RULES 202
#define SAVE_TO_END 203


Parser::Parser() {
	file = "";
	f = NULL;
}

Parser::Parser(string file) {
	Parser::setFile(file);
}

int Parser::setFile(string file) {
	this->file = file;
	fopen_s(&f,file.c_str(), "r");
	if (f == NULL) {
		return PARSER_FILE_NOT_FOUND;
	}
	return PARSER_DONE;
}

int Parser::parse() {
	int saveTo = -1;
	//int i = 0;

	char buf[LINE_MAX];
	char * token = NULL;
	char * nextToken = NULL;
	char * seps = " \n\t";

	if (f == NULL) return PARSER_FILE_NOT_FOUND;
	
	while (fgets(buf, sizeof buf, f) != NULL) {
		printf("FRASE ORIGINAL: %s\n", buf);
		token = strtok_s(buf, seps, &nextToken);
		printf("primeiro token: %s\n", token);
		//printf("primeiro char: %c\n", token[0]);
		while (token != NULL){
			//printf("ENTREI AQUI\n");
			if (token[0] == '%') {
				printf("COMMENT DETETADO\n");
				break;
			}
			if (strcmp(token, "#AXIOM") == 0) {
				saveTo = SAVE_TO_AXIOM;
				printf("AXIOMA DETETADO\n");
				break;
			}
			if (strcmp(token, "#DEGREES") == 0) {
				saveTo = SAVE_TO_DEGREE;
				printf("DEGREE DETETADO\n");
				break;
			}
			if (strcmp(token, "#PRODUCTION") == 0) {
				saveTo = SAVE_TO_PRODUCTION_RULES;
				printf("PRODUTION DETETADO\n");
				break;
			}
			if (strcmp(token, "#END") == 0) {
				saveTo = SAVE_TO_END;
				printf("FIM DETETADO\n");
				break;
			}

			printf("%s\n", token);
			token = strtok_s(NULL, seps, &nextToken);
		}

		if (saveTo == SAVE_TO_END) break;
	}
	
	parsed = true;
	return PARSER_DONE;
}

int Parser::clean() {
	if (f != NULL) {
		fclose(f);
		f = NULL;
	}
	file = "";
	axiom = NULL;
	productionRules = NULL;
	nProductionRules = 0;
	parsed = false;

	return PARSER_DONE;
}