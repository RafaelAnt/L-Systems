#pragma once
#include<iostream>

using namespace std;

class ProductionRule {
	char target;
	char * result;

public:
	ProductionRule(char target, char* result);
	char getTarget();
	char* getResult();
	//int separateProdRule(char * rule);
};