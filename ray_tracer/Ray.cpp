
//  Ray.cpp


#ifndef __ray_tracer__Ray__
#define __ray_tracer__Ray__

#include "vector2d.h"
#include "vector3d.h"

// ray
class Ray{
public:
	vector3d origin, normal, dir;
	
	Ray(vector3d o, vector3d d){
		origin = o;
		normal = d.normalize();
		dir = d;
	}
};

#endif /* defined(__ray_tracer__Ray__) */
