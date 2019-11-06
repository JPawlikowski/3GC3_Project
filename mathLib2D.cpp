// COMPSCI 3GC3
// Tyler Philips
// 400017512
// Assignment 1

#include <math.h>
#include "mathLib2D.h"
#include <iostream>
using namespace std;


//constructor without parameters
//mX- Point2D object's x variable
//mY- Point2D object's y variable
Point3D::Point3D(){
  this ->xpos = 0;
  this ->ypos = 0;
  this ->zpos = 0;
}

//function calculates distance between 2 points
//other - a Point2D object that is taken as a parameter
float Point3D::distanceTo(Point3D other){
	return sqrt((other.xpos-this ->xpos)*(other.xpos-this ->xpos) + (other.ypos-this ->ypos)*(other.ypos-this ->ypos)+ (other.zpos-this ->zpos)*(other.zpos-this ->zpos));
}

//function calculates distance between 2 points with a distance calculation that does not use square root
//other is a Point2D object that is taken as a parameter
float Point3D::fastDistanceTo(Point3D other){
	return (other.xpos-this ->xpos)*(other.xpos-this ->xpos) + (other.ypos-this ->ypos)*(other.ypos-this ->ypos)+ (other.zpos-this ->zpos)*(other.zpos-this ->zpos);
}





