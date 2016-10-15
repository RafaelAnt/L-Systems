#include <iostream>

#include "Parser.h"

using namespace std;

class Parser {
	string file;
	FILE *f;
	char * axiom;
	char ** productionRules;
	int nProductionRules;

public:
	Parser();
	Parser(string file);
	int setFile(string file);
	int parse();
	int clean();
};

Parser::Parser() {
	file = "";
	f = NULL;
}

Parser::Parser(string file) {
	Parser::setFile(file);
}

int Parser::setFile(string file) {
	this->file = file;
	f=fopen(file.data, "r");
	if (f == NULL) {
		return FILE_NOT_FOUND;
	}
	return DONE;
}

int Parser::parse() {
	long lSize;

	if (f == NULL) return FILE_NOT_FOUND;
	
	// obtain file size:
	fseek(f, 0, SEEK_END);
	lSize = ftell(f);
	rewind(f);

	fread(axiom, 1, 10, f);

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

	return DONE;
}