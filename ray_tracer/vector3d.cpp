
//  vector3d.cpp

#include "vector3d.h"

vector3d::vector3d(){
	x = ((float)rand() / RAND_MAX) * 2 - 1;
	y = ((float)rand() / RAND_MAX) * 2 - 1;
	z = ((float)rand() / RAND_MAX) * 2 - 1;
}

vector3d::vector3d(float x, float y, float z):x(x),y(y),z(z){}

vector3d vector3d::operator-() const{
	return vector3d(-x, -y, -z);
}

vector3d vector3d::operator+(const vector3d& addOperand) const{
	return vector3d(x + addOperand.x, y + addOperand.y, z + addOperand.z);
}

vector3d vector3d::operator-(const vector3d& operand) const{
	return vector3d(x - operand.x, y - operand.y, z - operand.z);
}

vector3d vector3d::operator*(const vector3d& operand) const{
	return vector3d(x * operand.x, y * operand.y, z * operand.z);
}

vector3d vector3d::operator/(const vector3d& operand) const{
	return vector3d(x / operand.x, y / operand.y, z / operand.z);
}


vector3d vector3d::operator*(float operand) const{
	return vector3d(x * operand, y * operand, z * operand);
}


vector3d vector3d::operator/(float operand) const{
	return vector3d(x / operand, y / operand, z / operand);
}


void vector3d::operator-=(const vector3d& a){
	x -= a.x;
	y -= a.y;
	z -= a.z;
}

void vector3d::operator+=(const vector3d& a){
	x += a.x;
	y += a.y;
	z += a.z;
}

void vector3d::operator*=(const vector3d& a){
	x *= a.x;
	y *= a.y;
	z *= a.z;
}

void vector3d::operator*=(float a){
	x *= a;
	y *= a;
	z *= a;
}

float vector3d::norm(){
	return sqrtf(x*x+y*y+z*z);
}

float vector3d::norm2(){
	return x*x+y*y+z*z;
}

vector3d vector3d::normalize(){
	float oneOverLength = 1.0f / norm();
	x *= oneOverLength;
	y *= oneOverLength;
	z *= oneOverLength;
	return *this;
}

vector3d vector3d::cross(const vector3d& operand) const{
	return vector3d(
				  y * operand.z - z * operand.y,
				  z * operand.x - x * operand.z,
				  x * operand.y - y * operand.x);
	
}

float vector3d::dot(const vector3d& operand) const{
	return x * operand.x + y * operand.y + z * operand.z;
}