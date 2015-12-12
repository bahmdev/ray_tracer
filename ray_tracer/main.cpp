//  main.cpp

#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <stdlib.h>
#include <float.h>


#include "vector2d.h"
#include "vector3d.h"
#include "LightSource.cpp"
#include "Ray.cpp"
#include "Material.cpp"
#include "Hit.cpp"
#include "Camera.cpp"
#include "Intersectable.cpp"
#include "Perlin.h"

// scene
class Scene{
	Camera camera;
	std::vector<LightSource*> lightSources;
	std::vector<Intersectable*> objects;
	std::vector<Material*> materials;
	
public:
	Scene(){
		
		
		//materials
		Material *lambertian = new Material();
		lambertian->kd = vector3d(0.3, 0.6, 0.4);
		lambertian->ks = vector3d(0, 0, 0);
		materials.push_back(lambertian);
		
		Material *phongBlinn = new Material();
		phongBlinn->kd = vector3d(0.2, 0, 0);
		phongBlinn->ks = vector3d(1,1,1);
		phongBlinn->shininess = 25;
		materials.push_back(phongBlinn);
		
		Material *lambertianPhongBlinn = new Material();
		lambertianPhongBlinn->kd = vector3d(0.3, 0.3, 0);
		lambertianPhongBlinn->ks = vector3d(1, 1, 1);
		lambertianPhongBlinn->shininess = 25;
		materials.push_back(lambertianPhongBlinn);
		
		Material *gold = new Material();
		gold->kd = vector3d(0.7, 0.5, 0.3);
		gold->ks = vector3d(0.8, 0.7, 0.4);
		gold->f0 = vector3d(0.4, 0.3, 0.2);
		gold->reflective = true;
		materials.push_back(gold);
		
		Material *silver = new Material();
		silver->kd = vector3d(0.1, 0.3, 0.3);
		silver->ks = vector3d(0.8, 0.7, 0.4);
		silver->f0 = vector3d(0.4, 0.3, 0.2);
		silver->reflective = true;
		materials.push_back(gold);
		
		Material *glass = new Material();
		glass->kd = vector3d(0,0,0);
		glass->ks = vector3d(0,0,0);
		glass->f0=vector3d(0,0,0);
		glass->n = 1.15;
		glass->refractive=true;
		materials.push_back(glass);
		
		Material *checker = new Material();
		checker->kd = vector3d(0.9,0.2,0.3);
		checker->ks = vector3d(0,0,0);
		checker->f0=vector3d(0.9,0.8,0.4);
		checker->shininess = 10;
		checker->n = 1;
		checker->twoDim = true;
		materials.push_back(checker);
		
		Material *marble = new Material();
		marble->kd = vector3d(1,1,1);
		marble->ks = vector3d(0,0,0);
		marble->f0 = vector3d(0.9, 0.8, 0.4);
		marble->shininess = 27.5;
		marble->n = 0.15;
		marble->threeDim = true;
		materials.push_back(marble);
		
		//lights
		lightSources.push_back(new PointLight(vector3d(-5, -0.1, -2), vector3d(2, 2, 2)));
		lightSources.push_back(new PointLight(vector3d(5, -0.1, -2), vector3d(2, 2, 2)));

		lightSources.push_back(new DirectionalLight(vector3d(0, 1, 0), vector3d(1, 1, 1)));
		lightSources.push_back(new DirectionalLight(vector3d(1, 0, 0), vector3d(1, 1, 1)));
		
		//plane
		objects.push_back(new Plane(vector3d(0, 0.5, 0), vector3d(0, -1.5, 0), lambertianPhongBlinn));

	
		//cube
		//objects.push_back(new Cube(vector3d(2, -5, -3), vector3d(3, 2, -2), lambertianPhongBlinn));
		
		
		//sphere
		//objects.push_back(new Sphere(vector3d(-5, 0, 0), 1.0, gold));

		
		
		//snowman
		snowman(0,		0,		0,		0.8,		phongBlinn);
		


		

		

	}
	
	void snowman(float x, float y, float z, float scale, Material* material){
		objects.push_back(new Sphere(vector3d(x, y+2.75*scale, z), 0.8*scale, material));
		objects.push_back(new Sphere(vector3d(x, y+1.5*scale,	z), 1.1*scale, material));
		objects.push_back(new Sphere(vector3d(x, y, z), 1.5*scale, material));
	}
	
	
	
	~Scene(){
		for (std::vector<LightSource*>::iterator iLightSource = lightSources.begin();
			 iLightSource != lightSources.end(); ++iLightSource) delete *iLightSource;
		for (std::vector<Material*>::iterator iMaterial = materials.begin();
			 iMaterial != materials.end(); ++iMaterial) delete *iMaterial;
		for (std::vector<Intersectable*>::iterator iObject = objects.begin();
			 iObject != objects.end(); ++iObject) delete *iObject;
	}
	
	
public:
	Camera& getCamera(){return camera;}
	
	//best hit
	Hit firstTraverse(const Ray &ray){
		Hit bestHit;
		bestHit.t = FLT_MAX;
		for (int i=0; i<objects.size(); i++){
			Hit h = objects[i]->intersect(ray);
			if (h.t > 0 && h.t < bestHit.t)
				bestHit = h;
		}
		return bestHit;
	}
	
	//trace
	vector3d trace(const Ray& ray, int depth){
		
		if (depth > 5)
			return vector3d(0,0,0);
		
		Hit h = firstTraverse(ray);
		
		if (h.t == FLT_MAX)
			return vector3d(0,0,0);
		
		vector3d luminosity = vector3d(0,0,0);
		
		
		//reflection
		if (h.material->reflective){
			
			Ray reflection(h.position+h.normal*0.01,
						   ray.dir - h.normal * ray.dir.dot(h.normal)*2);
			
			vector3d f0 = h.material->f0 + (vector3d(1,1,1)-h.material->f0)
			*powf(1 - (fabs(ray.normal.dot(h.normal))), 5);
			luminosity += trace(reflection, depth+1)*f0;
		}
		
		
		//refractive
		if (h.material->refractive){
			float d = h.normal.dot(ray.dir);
			float n1 = d < 0 ? h.material->n : 1;
			float n2 = d >= 0 ? h.material->n : 1;
			vector3d start = d < 0 ? h.position-h.normal*0.0001 : h.position+h.normal*0.0001;
			float c = ray.normal.dot(h.normal) < 0 ? -ray.normal.dot(h.normal) : ray.normal.dot(h.normal);
			float n = n2/n1;
			
			Ray refraction(start, ray.dir*n+h.normal*(n*c-sqrtf(1-n*n*(1-c*c))));
			vector3d f0 = h.material->f0 + (vector3d(1,1,1)-h.material->f0)
			*powf(1 - (fabs(ray.normal.dot(h.normal))), 5);
			
			luminosity += trace(refraction, depth+1)*(vector3d(1,1,1)-f0);
		}
		
		
		
		//textures
		float kdF2 = h.material->twoDim ? ((int(h.uv.x * 25)%2==0
											&& int(h.uv.y*25)%2==1) ? 0.85 : 0.15) : 1;
		float kdF3 = h.material->threeDim ? Perlin().marble(h.position) : 1;
		
		
		
		//lights
		for (int i=0; i<lightSources.size(); i++) {
			Ray shadow(h.position+h.normal*0.001,
					   lightSources[i]->getLightDirAt(h.position));
			
			Hit h2 = firstTraverse(shadow);
			
			if (h2.t < 0 || h2.t > lightSources[i]->getDistanceFrom(h.position)){
				
				float cosTeta = lightSources[i]->getLightDirAt(h.position).dot(h.normal);
				if (cosTeta<0)
					cosTeta = 0;
				vector3d half = lightSources[i]->getLightDirAt(h.position) - ray.dir;
				half.normalize();
				float cosDelta = half.dot(h.normal);
				if (cosDelta<0)
					cosDelta = 0;
				
				luminosity += lightSources[i]->getRadianceAt(h.position)*
				(h.material->kd*cosTeta+h.material->ks*powf(cosDelta, h.material->shininess));
			}
		}
		return luminosity*kdF2*kdF3;
	}
	
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// app data ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// rez
const int screenWidth = 600;
const int screenHeight = 600;

// output
vector3d image[screenWidth*screenHeight];

// scene
Scene scene;

// keys
std::vector<bool> keysPressed;

// calculates scanline of the image for all pixels
bool computeImage(){
	//std::cout << "computing new image \n";
	//static unsigned int p = 0;
	
	int p = 0;
	
	if(p >= 1)
		return false;
	for(int j = p; j < screenHeight; j++){
		for(int i = 0; i < screenWidth; i++){
			//vector3d pixelColor = vector3d(0, 0, 0);
			
			vector2d ndcPixelCentre( (2.0 * i - screenWidth) / screenWidth,
								  (2.0 * j - screenHeight) / screenHeight );
			
			Camera& camera = scene.getCamera();
			Ray ray = Ray(camera.getEye(), camera.rayDirFromNdc(ndcPixelCentre));
			
			image[j*screenWidth + i] = scene.trace(ray, 0);
		}

	}
	p++;
	return true;
}






////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// Open GL ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

void onDisplay(){
	std::cout << "*on display* \n";

	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene.getCamera().apply();
	
	computeImage();

	//if(computeImage()) glutPostRedisplay();
	
	glDrawPixels(screenWidth, screenHeight, GL_RGB, GL_FLOAT, image);
	glutSwapBuffers();
}


void onIdle() {
	double t = glutGet(GLUT_ELAPSED_TIME) * 0.001;
	static double lastTime = 0.0;
	double dt = t - lastTime;
	lastTime = t;
	
	scene.getCamera().move(dt, keysPressed);
	//glutPostRedisplay();
}


void onKeyboard(unsigned char key, int x, int y){
	std::cout << "key pressed \n";
	keysPressed.at(key) = true;
}

void onKeyboardUp(unsigned char key, int x, int y){
	std::cout << "key released \n";
	keysPressed.at(key) = false;
	glutPostRedisplay();

	
}

void onMouse(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON)
		if(state == GLUT_DOWN){
			std::cout << "mouse pressed \n";
			scene.getCamera().startDrag(x, y);
		} else{
			std::cout << "\nmouse released \n";
			scene.getCamera().endDrag();
			glutPostRedisplay();
		}
}

void onMouseMotion(int x, int y) {
	std::cout << "dragging ";
	scene.getCamera().drag(x, y);
}

void onReshape(int winWidth, int winHeight) {
	//not working
	glViewport(0, 0, winWidth, winHeight);
	scene.getCamera().setAspectRatio(
									 (float)winWidth/winHeight);
}


int main(int argc, char * argv[]){
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Ray Tracer");
	glViewport(0, 0, screenWidth, screenHeight);
	
	glutDisplayFunc(onDisplay);
	glutIdleFunc(onIdle);
	glutKeyboardFunc(onKeyboard);
	glutKeyboardUpFunc(onKeyboardUp);
	for(int i=0; i<256; i++) keysPressed.push_back(false);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMouseMotion);
	glutReshapeFunc(onReshape);
	
	
	glutMainLoop();
	
	return 0;
}



