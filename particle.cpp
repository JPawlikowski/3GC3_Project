#include <math.h>
#include <iostream>
#include "particle.h"
#include <vector>
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

// COMPSCI 3GC3
// Tyler Philips
// 400017512
// Assignment 3


//Particle constructor 
//set variables to random values
//origin is point (0,0,0)
Particle::Particle(){
  this ->xpos = 0;
  this ->ypos = 0;
  this ->zpos = 0;
  this ->xdir = rand()%20;     
  this ->ydir = .01;
  this ->zdir = .001;
  this ->r = (float)(rand() % 250)/255;
  this ->g = (float)(rand() %250)/255;
  this ->b = (float)(rand() % 250)/255;
  this ->size =((rand() % 18)+15);
  this ->age = 5500;
  this ->speed = 1;
  this ->maxHeight=(rand() % 10)+8;
  this ->material=(rand() % 3);
  this ->property=(rand() % 3);
  this ->fall=false;
}

//this fuction will return whether a particle is alive or not
bool Particle::alive(){
  if(this->age<=0){ return false; }
  else{ return true; }
}