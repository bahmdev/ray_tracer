
//  vector2d.h


#ifndef __ray_tracer__vector2d__
#define __ray_tracer__vector2d__

#pragma once
#include <stdio.h>
#include <iostream>
#include <math.h>

// vector 2d
class vector2d{
public:
	float x;
	float y;
	
	vector2d();
	vector2d(float x, float y);
	
	vector2d operator-() const;
	vector2d operator+(const vector2d& addOperand) const;
	vector2d operator-(const vector2d& operand) const;
	vector2d operator*(const vector2d& operand) const;
	vector2d operator*(float operand) const;
	
	void operator-=(const vector2d& a);
	void operator+=(const vector2d& a);
	void operator*=(const vector2d& a);
	void operator*=(float a);
	
	float norm();
	float norm2();
	vector2d normalize();
	
	static vector2d random();
};

#endif /* defined(__ray_tracer__vector2d__) */
