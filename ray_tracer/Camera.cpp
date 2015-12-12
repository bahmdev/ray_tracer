
//  Camera.cpp


#ifndef __ray_tracer__Camera__
#define __ray_tracer__Camera__

#include <stdio.h>
#include <vector>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "vector2d.h"
#include "vector3d.h"

// camera
class Camera{
	vector3d eye, ahead, right, up;
	vector2d tanFovHalf, lastMousePos, mouseDelta;
public:
	Camera(){
		eye =	vector3d(0, 0, 3);
		ahead = vector3d(0, 0, -1);
		right = vector3d(1, 0, 0);
		up =	vector3d(0, 1, 0);
		tanFovHalf = vector2d(1, 1);
	}
	vector3d getEye(){return eye;}
	vector3d rayDirFromNdc(const vector2d ndc){
		return (ahead+right*ndc.x*tanFovHalf.x+up*ndc.y*tanFovHalf.y).normalize();
	}
	
	void startDrag(int x, int y) {
		lastMousePos = vector2d(x, y);
	}
	void drag(int x, int y){
		vector2d mousePos(x, y);
		mouseDelta = mousePos - lastMousePos;
		lastMousePos = mousePos;
	}
	void endDrag(){
		mouseDelta = vector2d(0, 0);
	}
	
	void setCamera(vector3d pos, float oa){
		eye.x = pos.x;
		eye.y = pos.y;
		eye.z = pos.z;
		
	}
	
	void setAhead(float o){
		ahead = vector3d(-cos(o+90 * (M_PI)/180), 0, sin(o+90 * (M_PI)/180));
	}
	
	void move(float dt, std::vector<bool>& keysPressed) {
		
		 //std::cout << "moved camera with keys\n";
		
		 if(keysPressed.at('w'))
		 eye += ahead * dt * 20;
		 if(keysPressed.at('s'))
		 eye -= ahead * dt * 20;
		 if(keysPressed.at('a'))
		 eye -= right * dt * 20;
		 if(keysPressed.at('d'))
		 eye += right * dt * 20;
		 if(keysPressed.at('q'))
		 eye -= vector3d(0,1,0) * dt * 20;
		 if(keysPressed.at('e'))
		 eye += vector3d(0,1,0) * dt * 20;
		
		
		 float yaw = atan2f( ahead.x, ahead.z );
		 float pitch = -atan2f( ahead.y,
		 sqrtf(ahead.x * ahead.x + ahead.z * ahead.z) );
		 
		 yaw -= mouseDelta.x * 0.02f;
		 pitch += mouseDelta.y * 0.02f;
		 if(pitch > 3.14/2) pitch = 3.14/2;
		 if(pitch < -3.14/2) pitch = -3.14/2;
		 
		 mouseDelta = vector2d(0, 0);
		 
		 ahead = vector3d(sin(yaw)*cos(pitch), -sin(pitch),
		 cos(yaw)*cos(pitch) );
		 right = ahead.cross(vector3d(0, 1, 0)).normalize();
		 up = right.cross(ahead);
		
	}
	
	
	void setAspectRatio(float ar)  {
		tanFovHalf.x = ar * tanFovHalf.y;
	}
	
	void apply(){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(atan(tanFovHalf.y)*2/3.14*180,
					   tanFovHalf.x / tanFovHalf.y, 0.1, 500);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(
				  eye.x, eye.y, eye.z,
				  eye.x+ahead.x, eye.y+ahead.y, eye.z+ahead.z,
				  0.0, 1.0, 0.0);
	}
};

#endif /* defined(__ray_tracer__Camera__) */
