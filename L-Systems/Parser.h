#pragma once
#include<iostream>

#define PARSER_DONE 0
#define PARSER_FILE_NOT_FOUND 100

using namespace std;

class Parser {
	string file;
	FILE *f;
	char * axiom;
	char ** productionRules;
	int nProductionRules;
	bool parsed;

public:
	Parser();
	Parser(string file);
	int setFile(string file);
	int parse();
	int clean();
};