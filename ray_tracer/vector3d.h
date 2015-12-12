
//  vector3d.h


#ifndef __ray_tracer__vector3d__
#define __ray_tracer__vector3d__

#pragma once
#include <stdio.h>
#include <iostream>
#include <math.h>

// vector 3d
class vector3d{
	
public:
	float x;
	float y;
	float z;
	
	vector3d();
	vector3d(float x, float y, float z);
	
	vector3d operator-() const;
	vector3d operator+(const vector3d& addOperand) const;
	vector3d operator-(const vector3d& operand) const;
	vector3d operator*(const vector3d& operand) const;
	vector3d operator/(const vector3d& operand) const;
	vector3d operator*(float operand) const;
	vector3d operator/(float operand) const;
	
	void operator-=(const vector3d& a);
	void operator+=(const vector3d& a);
	void operator*=(const vector3d& a);
	void operator*=(float a);
	
	float norm();
	float norm2();
	vector3d normalize();
	
	vector3d cross(const vector3d& operand) const;
	float dot(const vector3d& operand) const;
};

#endif /* defined(__ray_tracer__vector3d__) */
