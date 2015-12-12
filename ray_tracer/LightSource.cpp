
//  ray_tracer


#ifndef __ray_tracer__LightSource__
#define __ray_tracer__LightSource__

#include <stdio.h>
#include "vector3d.h"

// abstract Light Source
class LightSource{
public:
	virtual vector3d getRadianceAt ( vector3d x )=0; 
	virtual vector3d getLightDirAt ( vector3d x )=0;
	virtual float getDistanceFrom( vector3d x )=0;
};

// directional light
class DirectionalLight : public LightSource{
public:
	vector3d direction, radiance;
	
	DirectionalLight(vector3d d, vector3d r){
		direction = d;
		radiance = r;
	}
	vector3d getRadianceAt(vector3d p){return radiance;}
	vector3d getLightDirAt(vector3d p){return direction;}
	float getDistanceFrom(vector3d p){return 10000000;}
};


// point light
class PointLight : public LightSource{
public:
	vector3d position, power;
	
	PointLight(vector3d pos, vector3d pow){
		position = pos;
		power = pow;
	}
	vector3d getRadianceAt(vector3d p){return power * (1 / (position-p).dot(position-p));}
	vector3d getLightDirAt(vector3d p){return (position-p).normalize();}
	float getDistanceFrom(vector3d p){return (position-p).norm();}
};

#endif /* defined(__ray_tracer__LightSource__) */
