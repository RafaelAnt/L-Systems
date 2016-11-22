#include <iostream>
#include <stdio.h>

#include "ProductionRule.h"


ProductionRule::ProductionRule(char target, char* result) {
	this->result = (char*)malloc(sizeof(char)*strlen(result) + 1);
	this->target = target;
	strcpy(this->result, result);
}

char ProductionRule::getTarget() {
	return this->target;
}

char* ProductionRule::getResult() {
	//printf("Teste\n");
	char* aux = (char*)malloc(sizeof(char) * strlen(result) + 1);
	strcpy(aux, result);
	return aux;
	//printf("Teste 2\n");
}