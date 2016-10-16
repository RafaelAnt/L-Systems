#include <iostream>
#include <stdio.h>

#include "Parser.h"

#define LINE_MAX 500
#define SAVE_TO_AXIOM 200
#define SAVE_TO_DEGREE 201
#define SAVE_TO_PRODUCTION_RULES 202
#define SAVE_TO_END 203

#define TYPE_AXIOM 300
#define TYPE_DEGREE 301
#define TYPE_PRODUCTION 302


Parser::Parser() {
	file = "";
	f = NULL;
	nProductionRules = 0;
	//productionRules = list<ProductionRule>();
	parsed = false;
	degree = 0;
	axiom = (char *) malloc(LINE_MAX);
}

Parser::Parser(string file) {
	Parser::setFile(file);
	nProductionRules = 0;
	parsed = false;
	degree = 0;
	axiom = (char *)malloc(LINE_MAX);
}

int Parser::setFile(string file) {
	this->file = file;
	fopen_s(&f,file.c_str(), "r");
	if (f == NULL) {
		return PARSER_FILE_NOT_FOUND;
	}
	return PARSER_DONE;
}

int separate(char* prodRule, char * target, char** result) {
	int i = 0;
	char* esq, *dir = NULL;
	int equals = 0;

	while (prodRule[i] != NULL && prodRule[i] != '\0') {
		if (prodRule[i] == '=') equals++;
		i++;
	}
	if (equals != 1) return PARSER_PRODUCTION_RULE_EQUALS_ERROR;

	esq = strtok_s(prodRule, "=", &dir);

	
	//gprintf("Sizeof esq: %d\n", strlen(esq));
	if (strlen(esq) > 1) return PARSER_PRODUCTION_RULE_MORE_THAN_1_LEFT;
	if (!isalpha(esq[0])) return PARSER_PRODUCTION_RULE_INVALID_CHARACTERS;

	//printf("Esq: %s\n", esq);
	//printf("Dir: %s\n", dir);

	*target = esq[0];
	*result = dir;
	//printf("Result: %s\n", *result);

	return PARSER_DONE;
}

int Parser::parse() {
	int saveTo = -1;
	//int i = 0;

	char buf[LINE_MAX];
	char * token = NULL;
	char * nextToken = NULL;
	char * seps = " \n\t";
	bool justTag = false;
	char c;
	char *s2 = NULL;
	int r;

	if (f == NULL) return PARSER_FILE_NOT_FOUND;
	
	while (fgets(buf, sizeof buf, f) != NULL) {
		//printf("FRASE ORIGINAL: %s\n", buf);
		token = strtok_s(buf, seps, &nextToken);
		//printf("primeiro token: %s\n", token);
		//printf("primeiro char: %c\n", token[0]);
		while (token != NULL){
			//printf("ENTREI AQUI\n");
			if (token[0] == '%') {
				//printf("COMMENT DETETADO\n");
				break;
			}
			if (strcmp(token, "#AXIOM") == 0) {
				saveTo = SAVE_TO_AXIOM;
				//printf("AXIOMA DETETADO\n");
				break;
			}
			if (strcmp(token, "#DEGREES") == 0) {
				saveTo = SAVE_TO_DEGREE;
				//printf("DEGREE DETETADO\n");
				break;
			}
			if (strcmp(token, "#PRODUCTION") == 0) {
				saveTo = SAVE_TO_PRODUCTION_RULES;
				//printf("PRODUTION DETETADO\n");
				break;
			}
			if (strcmp(token, "#END") == 0) {
				saveTo = SAVE_TO_END;
				//printf("FIM DETETADO\n");
				break;
			}
			
			switch (saveTo) {
			case(-1):
				return PARSER_SYNTAX_ERROR;

			case(SAVE_TO_AXIOM):
				if (hasInvalidChar(TYPE_AXIOM, token)) {
					return PARSER_AXIOM_INVALID_CHARACTERS;
				}
				strcpy_s(axiom, sizeof token, token);
				printf("AXIOMA: %s\n", axiom);
				break;

			case(SAVE_TO_DEGREE):
				if (hasInvalidChar(TYPE_DEGREE, token)) {
					return PARSER_DEGREE_INVALID_CHARACTERS;
				}
				degree = (float) atof(token);
				printf("GRAU: %f\n", degree);
				break;
				
			case(SAVE_TO_PRODUCTION_RULES):
				

				if (hasInvalidChar(TYPE_PRODUCTION, token)) {
					return PARSER_PRODUCTION_RULE_INVALID_CHARACTERS;
				}
				
				r = separate(token, &c, &s2);
				if (r == PARSER_DONE) {
					printf("PRODUTION RULE: %c = %s\n", c, s2);
				}
				else {
					return r;
				}
				
				break;

			default:
				return PARSER_UNKNOWN_ERROR;
			}
			

			//printf("%s\n", token);
			token = strtok_s(NULL, seps, &nextToken);
		}

		if (saveTo == PARSER_DONE) break;


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
	productionRules.clear();
	nProductionRules = 0;
	parsed = false;
	degree = 0;

	return PARSER_DONE;
}

bool Parser::hasInvalidChar(int type, char* string) {
	int i = 0;
	char axiomValidChars[] = "QWERTYUIOPASDFGHJKLZXCVBNM-+";
	char productionValidChars[] = "QWERTYUIOPASDFGHJKLZXCVBNM-+[]=";

	//printf("%s\n", &string[0]);

	switch (type){
	case(TYPE_AXIOM):
		while (string[i] != NULL && string[i] != '\0') {
			if (strchr(axiomValidChars, string[i]) == NULL) return true;
			i++;
		}
		break;

	case(TYPE_DEGREE):
		while (string[i] != NULL && string[i]!='\0') {
			if (!isdigit(string[i])) return true;
			i++;
		}
		break;

	case(TYPE_PRODUCTION):
		bool hasEquals = false;
		while (string[i] != NULL && string[i] != '\0') {
			if (strchr(productionValidChars, string[i]) == NULL) return true;
			i++;
		}
		break;
	}

	return false;
}



ProductionRule::ProductionRule(char target, char* result) {
	this->target = target;
	strcpy_s(this->result, sizeof result, result);
}