#include "Point.h"

Point::Point() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Point::Point(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Point::~Point() {
}

float * Point::toVec3f(){
	float vec[3] = { x, y, z };
	return vec;
}