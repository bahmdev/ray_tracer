
//  Hit.cpp

#ifndef __ray_tracer__Hit__
#define __ray_tracer__Hit__

#include <stdio.h>
#include "vector2d.h"
#include "vector3d.h"
#include "Material.cpp"

// hit
class Hit{
public:
	Hit(){ t = -1; }
	float t, tExit;
	vector3d position, normal;
	vector2d uv;
	Material* material;
};

#endif /* defined(__ray_tracer__Hit__) */
