
//  Intersectable.cpp



#ifndef __ray_tracer__Intersectable__
#define __ray_tracer__Intersectable__

#include <stdio.h>
#include <float.h>
#include <vector>
#include "vector2d.h"
#include "vector3d.h"
#include "Material.cpp"
#include "Hit.cpp"
#include "Ray.cpp"

// abstract base class.
class Intersectable{
protected:
	Material* material;
public:
	Intersectable(Material* material):material(material) {}
	virtual Hit intersect(const Ray& ray)=0;
};

// sphere
class Sphere : public Intersectable{
	vector3d center;
	float radius;
public:
	Sphere(const vector3d& center, float radius, Material* material):
	Intersectable(material),
	center(center),
	radius(radius){}
	Hit intersect(const Ray& ray){
		vector3d diff = ray.origin - center;
		// quadratic equation coefficients
		double a = ray.dir.dot(ray.dir);
		double b = diff.dot(ray.dir) * 2.0;
		double c = diff.dot(diff) - radius * radius;
		
		double discr = b * b - 4.0 * a * c;
		if ( discr < 0 )
			return Hit();
		double sqrt_discr = sqrt( discr );
		double t1 = (-b + sqrt_discr)/2.0/a;
		double t2 = (-b - sqrt_discr)/2.0/a;
		
		float t = (t1<t2)?t1:t2;
		if(t < 0)
			t = (t1<t2)?t2:t1;
		if (t < 0)
			return Hit();
		
		Hit h;
		h.t = t;
		h.material = material;
		h.position = ray.origin + ray.dir * t;
		h.normal = h.position - center;
		h.normal.normalize();
		h.uv = vector2d( h.normal.dot(vector3d(0, 1, 0)) * 0.5 + 0.5,
					  atan2(h.normal.z, h.normal.x) / (2 * M_PI) + 0.5 );
		return h;
	}
};

// plane
class Plane : public Intersectable{
	vector3d normal, x0;
public:
	Plane(const vector3d& normal, const vector3d& x0, Material* material):
	Intersectable(material),
	normal(normal),
	x0(x0){}
	
	Hit intersect(const Ray& ray){
		float t = (x0.dot(normal) - ray.origin.dot(normal)) / ray.dir.dot(normal);
		if(t<0)
			return Hit();
		
		Hit h;
		h.t = t;
		h.tExit = FLT_MAX;
		h.material = material;
		h.position = ray.origin + ray.dir * h.t;
		h.normal = normal;
		h.normal.normalize();
		vector3d tangent = normal.cross(vector3d(0, 1, 0));
		if(tangent.norm() < 0.1)
			tangent = normal.cross(vector3d(1, 0, 0));
		vector3d binormal = normal.cross(tangent);
		h.uv = vector2d( (h.position-x0).dot(tangent), (h.position-x0).dot(binormal));
		return h;
	}
};






#endif /* defined(__ray_tracer__Intersectable__) */

