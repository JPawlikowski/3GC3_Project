#include <math.h>
#include <iostream>
#include <vector>
#include "mathLib2D.h"
#include <ctime>
#define KEY_UP 72

#define KEY_DOWN 80
using namespace std;

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#ifndef PARTICLE_H
#define PARTICLE_H
// COMPSCI 3GC3
// Tyler Philips
// 400017512
// Assignment 3


class Particle: public Point3D{

private:
  
        //colour variables
        float r;
        float g;
        float b;
        //size variable
        float size;
        int speed;
        int age;
        float maxHeight;
        int material;
      
        //direction variables
        float xdir;
        float ydir;
        float zdir;
        //rotation variables
        float xrot;
        float yrot;
        float zrot;
        //list for particle trail
        // vector<Point3D> trail;
        float property;
        bool fall;

public:
         //constructor with inputs on window dimensions
         Particle();
         //explosion particles
         Particle(float x, float y, float z);
         //return Particle values, including colour and coordinates and size  
         //getter functions
         float getX(){return xpos;}
         float getY(){return ypos;}
         float getZ(){return zpos;}
         float getDX(){return xdir;}
         float getDY(){return ydir;}
         float getDZ(){return zdir;}
         float getR(){return r;}
         float getG(){return g;}
         float getB(){return b;}
         float getSize(){return size;}
         int getSpeed(){return speed;}
         int getAge(){return age;}
         int getMaterial(){return material;}
         float getMaxHeight(){return maxHeight;}
         float getProperty(){return property;}
         float getMetalFall(){return fall;}
         // vector<Point3D> getTrail(){return trail;}
         bool alive();         
         //setter functions
         void setXYZ(float xI, float yI, float zI){this->xpos = xI;this->ypos=yI;this->zpos=zI;}
         void setDXYZ(float xI, float yI, float zI){this->xdir = xI;this->ydir=yI;this->zdir=zI;}
         void setR(float red){this->r=red;}
         void setG(float green){this->g=green;}
         void setB(float blue){this->b=blue;}
         void setSpeed(int s){this->speed=s;}
         void setMaxHeight(float h){this->maxHeight=h;}
         void setAge(){this->age-=1;}
         void setMetalFall(){this->fall=true;}

         void incSpeed(){this->speed+=.031;}

         // void addTrail(Point3D dot){this->trail.push_back(dot);}
};
#endif