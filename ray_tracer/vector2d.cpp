
//  vector2d.cpp

#include "vector2d.h"

vector2d::vector2d(){
	x = 0.0f;
	y = 0.0f;
}

vector2d::vector2d(float x, float y):x(x),y(y){}

vector2d vector2d::operator-() const{
	return vector2d(-x, -y);
}

vector2d vector2d::operator+(const vector2d& addOperand) const{
	return vector2d(x + addOperand.x, y + addOperand.y);
}

vector2d vector2d::operator-(const vector2d& operand) const{
	return vector2d(x - operand.x, y - operand.y);
}

vector2d vector2d::operator*(const vector2d& operand) const{
	return vector2d(x * operand.x, y * operand.y);
}

vector2d vector2d::operator*(float operand) const{
	return vector2d(x * operand, y * operand);
}

void vector2d::operator-=(const vector2d& a){
	x -= a.x;
	y -= a.y;
}

void vector2d::operator+=(const vector2d& a){
	x += a.x;
	y += a.y;
}

void vector2d::operator*=(const vector2d& a){
	x *= a.x;
	y *= a.y;
}

void vector2d::operator*=(float a){
	x *= a;
	y *= a;
}

float vector2d::norm(){
	return sqrtf(x*x+y*y);
}

float vector2d::norm2(){
	return x*x+y*y;
}

vector2d vector2d::normalize(){
	float oneOverLength = 1.0f / norm();
	x *= oneOverLength;
	y *= oneOverLength;
	return *this;
}

vector2d vector2d::random(){
	return vector2d(
				  ((float)rand() / RAND_MAX) * 2 - 1,
				  ((float)rand() / RAND_MAX) * 2 - 1);
}