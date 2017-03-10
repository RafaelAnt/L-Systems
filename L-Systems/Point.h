#pragma once

using namespace std;

#define POINT_DONE 400

class Point{
public:
	float x;
	float y;
	float z;

	Point();
	Point(float x, float y, float z);
	~Point();

	float * toVec3f();


private:

};



