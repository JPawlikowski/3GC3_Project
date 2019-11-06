// COMPSCI 3GC3
// Tyler Philips
// 400017512
// Assignment 3
#include <math.h>
#include <iostream>
#include "particle.h"
#include "mathLib2D.h"
#include <vector>
#include <string>
#define KEY_UP 72

#define KEY_DOWN 80
#include <stdio.h>
#include <stdlib.h>

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

//global variables

vector<Particle> particles;

// LIGHTING -- SET LIGHTING PARAMETERS 
GLfloat lightPos[2][4] = {
    { 5, -25, 5, 1 },
    { -5, 5, 5, 0 },
};

float amb[4] = {0,0,0,0}; //settings for light characteristics
float spec[4] = {1,1,1,1};
float eye[3] = {30,30,30};
float diff[4] = {.7,.7,.7,1};

float floorCoord[4][3]={{-10,0,0},{10,0,10},{10,0,-10},{0,0,10}};

//material variable
GLfloat materialAmbient[4] = {0,0,0,1};
GLfloat materialSpecular[4] = {.5,.5,.5,1};
GLfloat materialDiffuse[4] = {1,0,0,1};
GLfloat materialShininess[] = {10.0};


bool reset=false;
int count=0;

//this function is called once at the beginning of the program to print instructions for user
void instructions()
{
  cout<<"WELCOME TO PARTICLE  FOUNTAIN SIMULATOR" <<endl;
  cout<<"======================================="<<endl;
  cout<<"mouse- control target"  <<endl;
  cout<<"right click- fire paintball"<<endl;

}


//this funciton will draw a floor
//if user inputs instructs, open hole in floor
void floor(){
    ::floorCoord;
    glBegin(GL_QUADS);
    
    glColor3f(0,0.5,.5);
    // glVertex3f(-floorDim,0,floorDim);
    // glVertex3f(floorDim,0,floorDim);
    // glVertex3f(floorDim,0,-floorDim);
    // glVertex3f(-floorDim,0,-floorDim);

    for(int i=0;i<4;i++){
             glVertex3f(floorCoord[i][0],floorCoord[i][1],floorCoord[i][2]);
        }
    

    

    glEnd();
}

    
//this function is used to move particle objects
//including bouncing and speed
void moveDirection(){
   
}


//this function displays output to the window
void display(void) {

    // call global variables
    ::reset;
    ::count;

    //call glut functions
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 100);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], 0, 0, 0, 0, 1, 0);

    //if initial run of program
    //print instructions and reset particles
    if(reset==true){
        instructions();
        reset=false;
    }

    if(count%400 ==0){
        cout<<"we counting"<<endl;
    }

    // LIGHTING, SET CHANNELS 
    for (unsigned int i = 0; i < 2; i++) {
        glLightfv(GL_LIGHT0 + i, GL_POSITION, lightPos[i]);
        glLightfv(GL_LIGHT0 +i,GL_AMBIENT, amb);
        glLightfv(GL_LIGHT0 +i,GL_DIFFUSE, diff);
        glLightfv(GL_LIGHT0 +i,GL_SPECULAR,spec);
    }
    //draw floor
    floor();

    count++;

    //switch our buffers for a smooth animation
    glutSwapBuffers();

    //force a redisplay, to keep the animation running
    glutPostRedisplay();
}


//react to users keyboard input
void handleKeyboard(unsigned char key, int _x, int _y) {
    //CALL GLOBAL VARIABLES
    ::reset;
     //close window
    if (key == 'q' or key == 'Q') {
        exit(0);
    }
    if (key == 'r' or key == 'R') {
        reset=true;
    }
    
}
void handleSpecialKeyboard(int key, int _x, int _y) {
    
    if(key==GLUT_KEY_LEFT){

        cout<<"left"<<endl;
    }
    if(key==GLUT_KEY_RIGHT){
       cout<<"right"<<endl;
    }

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);     //starts up GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    //create window
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Paintball Range");  //creates the window
    
    //enable Z buffer test, otherwise things appear in the order they're drawn
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glShadeModel(GL_SMOOTH);
    glutKeyboardFunc(handleKeyboard);
    glutSpecialFunc(handleSpecialKeyboard);
    glutDisplayFunc(display);

    glutMainLoop();             //starts the event glutMainLoop

    return 0;

}
