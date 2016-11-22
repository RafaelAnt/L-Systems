#pragma once
#include <iostream>
#include <list>

using namespace std;

class TreeBranch {
	float width;
	float length;
	int stage;
	list<TreeBranch> branches;
	float color[3];

public:
	TreeBranch();
	int grow(string prodRule);
};