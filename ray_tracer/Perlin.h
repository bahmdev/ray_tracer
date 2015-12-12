#ifndef __ray_tracer__Perlin__
#define __ray_tracer__Perlin__

#include <stdio.h>
#include "vector3d.h"

// perlin noise
class Perlin{
	static float fade(float t){ return t * t * t * (t * (t * 6 - 15) + 10);}
	static float lerp(float t, float a, float b){ return a + t * (b - a);}
	
	static float grad(int hash, float x, float y, float z){
		int h = hash & 15;
		float u = h<8||h==12||h==13 ? x : y, 
		v = h < 4||h == 12||h == 13 ? y : z;
		return ((h & 1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
	}
	
public:
	int p[512];
	Perlin(void);
	float noise(vector3d pos);
	float marble(vector3d pos);
};


#endif /* defined(__ray_tracer__Perlin__) */
