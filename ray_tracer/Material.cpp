
//  Material.cpp

#ifndef __ray_tracer__Material__
#define __ray_tracer__Material__

#include <stdio.h>
#include "vector3d.h"

// material
class Material{
public:
	bool reflective, refractive, textured, twoDim, threeDim;
	float shininess, n;
	vector3d f0, kd, ks, er;
	
	Material(){
		reflective = false;
		refractive = false;
		textured = false;
		twoDim = false;
		threeDim = false;
		shininess = 15;
		n = 1;
		f0 = vector3d(0.93, 0.85, 0.4);
		kd = vector3d(0.5, 0.5, 0.5) + kd * 0.5;
		ks = vector3d(1, 1, 1);
		er = vector3d(0,0,0);
	}
};

#endif /* defined(__ray_tracer__Material__) */
