#include "Vec2.h"
#include "Vec2.h"
#include <math.h> 

/*
Starts the vector with 0 values
*/
Vec2::Vec2() {
	x = 0;
	y = 0;
}
/*
Starts the vector with set values
@param x: value in x
@param y: value in y
*/
Vec2::Vec2(int x, int y) {
	this->x = x;
	this->y = y;
}
/*
Compares 2 vectors
@param other: vector to compare
@return bool if the comparation is correct
*/
bool Vec2::operator<(const Vec2 other) {
	if (x < other.x && y < other.y)
		return true;
	return false;
}
/*
Compares 2 vectors
@param other: vector to compare
@return bool if the comparation is correct
*/
bool Vec2::operator>(const Vec2 other) {
	if (x > other.x&& y > other.y)
		return true;
	return false;
}
/*
Adds 2 vectors
@param other: vector to add
@return resulting vector
*/
Vec2 Vec2::operator+(const Vec2 other) {
	Vec2 v;
	v.x = x + other.x;
	v.y = y + other.y;
	return v;
}
/*
Subtracts 2 vectors
@param other: vector to substract
@return resulting vector
*/
Vec2 Vec2::operator-(const Vec2 other) {
	Vec2 v;
	v.x = x - other.x;
	v.y = y - other.y;
	return v;
}
/*
Multiplies a vector with an int
@param n: int to multiply
@return resulting vector
*/
Vec2 Vec2::operator*(int n) {
	Vec2 v;
	v.x = x * n;
	v.y = y * n;
	return v;
}
/*
Equals this vector to other
@param other: vector to equal
*/
void Vec2::operator=(const Vec2 other) {
	x = other.x;
	y = other.y;
	setSize();
}
/*
Divides vector parameters with a number
@param n: divisor
@return resulting vector
*/
Vec2 Vec2::operator/(int n) {
	Vec2 v;
	v.x = x / n;
	v.y = y / n;
	return v;
}
/*
Compares 2 vectors
*/
bool Vec2::operator==(const Vec2 other) {
	if (x == other.x && y == other.y)
		return true;
	else
		return false;
}

/*
Adds and equals 2 vectors
*/
void Vec2::operator+=(const Vec2 other) {
	x += other.x;
	y += other.y;
	setSize();
}

void Vec2::operator-=(const Vec2 other) {
	x += other.x;
	y += other.y;
	setSize();
}

/*
Unit vector in the direction of the vector
*/
Vec2 Vec2::normalize() {
	Vec2 v(x, y);
	return v / size;
}

void Vec2::setSize() {
	size = (x * x) + (y * y);
	size = sqrt(size);
}

Vec2::~Vec2() {

}