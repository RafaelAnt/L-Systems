#include <iostream>
#include <stdio.h>

#include "Parser.h"

int main() {
	
	Parser p = Parser();
	
	if (p.setFile("grammar.txt") == PARSER_FILE_NOT_FOUND) return -1;
	
	p.parse();
	//system("pause");
	printf("\nThe End!\n");
	return 0;
}