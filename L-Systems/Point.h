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

	Point& operator=(const Point& src);
	Point operator*(const Point& alt);
	Point operator/(const Point& alt);
	Point operator-(const Point& alt);
	Point operator+(const Point& alt);
	Point operator*(float num);
	Point operator/(float num);
	Point operator-(float num);
	Point operator+(float num);
	Point operator*=(const Point& alt);
	Point operator/=(const Point& alt);
	Point operator-=(const Point& alt);
	Point operator+=(const Point& alt);
	Point operator*=(float num);
	Point operator/=(float num);
	Point operator-=(float num);
	Point operator+=(float num);

	float * toVec3f();



private:

};



