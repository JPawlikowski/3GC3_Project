// COMPSCI 3GC3
// Tyler Philips & Jakub Pawlikowski
// 400017512 & 400011899
// Final Project
#include <math.h>
#include <iostream>
#include "Paintball.h"
#include "Splatter.h"
#include <vector>
#include <string>

//what are these?
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
std::vector<Paintball> paintBallVec(0);
std::vector<Splatter> splatterVec(0);
//bool shot = false;
bool reset = false;
int cnt = 0;

//crosshair coordinates
float crossHairPos[3] = {0, 9, 47};

// One light for now
GLfloat lightPos[1][4] = {
    { 5, 25, 5, 1 },
};

//camera position
float eye[3] = {0, 10, 50};

//some basic lighting characteristics
float amb[4] = {0,0,0,0};
float spec[4] = {1,1,1,1};
float diff[4] = {.7,.7,.7,1};

//Floor map coordinates
float floorCoord[4][3]={
    {-20, 0, -20},
    {-20, 0, 20},
    {20, 0, -20},
    {20, 0, 20}
};

//material variables
GLfloat materialAmbient[4] = {0,0,0,1};
GLfloat materialSpecular[4] = {.5,.5,.5,1};
GLfloat materialDiffuse[4] = {1,0,0,1};
GLfloat materialShininess[] = {10.0};

//this function is called once at the beginning of the program to print instructions for user
void instructions()
{
  cout<<"WELCOME TO 3D PAINTBALL SIMULATOR" <<endl;
  cout<<"======================================="<<endl;
  cout<<"mouse- control target"  <<endl;
  cout<<"right click- fire paintball"<<endl;

}


//this funciton will draw a floor
//if user inputs instructs, open hole in floor
void floor(){
    //::floorCoord;
    glBegin(GL_POLYGON);
        glColor3f(0,0.5,.5);
        glVertex3f(-20,0,-40);
        glVertex3f(20,0,-40);
        glVertex3f(20,0,40);
        glVertex3f(-20,0,40);
    glEnd();
    

    // for(int i=0;i<4;i++){
    //          glVertex3f(floorCoord[i][0],floorCoord[i][1],floorCoord[i][2]);
    //     }
    
}

void wall(){
    //use variables from arrays here not raw numbers 'WALL_POS'
    glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glVertex3f(-15, 0, -35);
        glVertex3f(15, 0, -35);
        glVertex3f(15, 20, -35);
        glVertex3f(-15, 20, -35);
    glEnd();
}

//draw x,y,z axis, useful for perspective and testing
void drawAxis() {
    glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(0,0,0);
        glVertex3f(50,0,0);
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,50,0);
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,50);
    glEnd();
}

//draw aiming point
void drawCrossHair() {
    glBegin(GL_LINES);
        glColor3f(0,0,0);
        glVertex3f(crossHairPos[0] - 0.1, crossHairPos[1], crossHairPos[2]);
        glVertex3f(crossHairPos[0] + 0.1, crossHairPos[1], crossHairPos[2]);
        glVertex3f(crossHairPos[0], crossHairPos[1] + 0.1, crossHairPos[2]);
        glVertex3f(crossHairPos[0], crossHairPos[1] - 0.1, crossHairPos[2]);
    glEnd();
}

//draw splatters on wall
void drawSplatters() {    //note: add color of paintball to this
    for(int i = 0; i < splatterVec.size(); i++){
        glBegin(GL_POLYGON);
            glColor3f(0,0,0);
            glVertex3f(splatterVec[i].mX - 2, splatterVec[i].mY - 2, -34);
            glVertex3f(splatterVec[i].mX + 2, splatterVec[i].mY - 2, -34);
            glVertex3f(splatterVec[i].mX + 2, splatterVec[i].mY + 2, -34);
            glVertex3f(splatterVec[i].mX - 2, splatterVec[i].mY + 2, -34);
            glVertex3f(splatterVec[i].mX - 2, splatterVec[i].mY - 2, -34);
        glEnd();
    }
}

//add to vector of splatters
void wallInteraction(int i) {
    cout<<"hit"<<endl;
    Splatter S(paintBallVec[i].mX, paintBallVec[i].mY);
    splatterVec.push_back(S);
    paintBallVec.erase(paintBallVec.begin()+i)
}

//shooting a paintball ads it to the vector
void shootPaintBall(){
    Paintball P(crossHairPos[0], crossHairPos[1], crossHairPos[2]);
    paintBallVec.push_back(P);
}

//increment z value of all active paintballs
void drawPaintBalls(){
    for(int i = 0; i < paintBallVec.size(); i++){
        glPushMatrix();
            glColor3f(0,0,0);
            paintBallVec[i].mZ = paintBallVec[i].mZ - paintBallVec[i].speed;    //"-" because shooting 'down' range
            glTranslatef(paintBallVec[i].mX, paintBallVec[i].mY, paintBallVec[i].mZ);
            if (paintBallVec[i].mZ <= -35) {    //hit wall
                wallInteraction(i);
            }
            glutSolidSphere(0.5, 10, 10);
        glPopMatrix();
    }
}



//this function displays output to the window
void display(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0],eye[1],eye[2], 0,10,0, 0,1,0);

    //if initial run of program
    //print instructions and reset particles
    if(reset == true){
        instructions();
        reset = false;
    }

    //if(count%400 == 0){
        //cout<<"we counting"<<endl;  //LMAO nice T
    //}

    // LIGHTING, SET CHANNELS 
    // for (unsigned int i = 0; i < 2; i++) {
    //     glLightfv(GL_LIGHT0 + i, GL_POSITION, lightPos[i]);
    //     glLightfv(GL_LIGHT0 +i,GL_AMBIENT, amb);
    //     glLightfv(GL_LIGHT0 +i,GL_DIFFUSE, diff);
    //     glLightfv(GL_LIGHT0 +i,GL_SPECULAR,spec);
    // }

    drawAxis();

    //draw floor
    floor();

    wall();

    drawCrossHair();

    drawPaintBalls();

    drawSplatters();

    //switch our buffers for a smooth animation
    glutSwapBuffers();

    //force a redisplay, to keep the animation running
    glutPostRedisplay();
}

void projection(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1,1,100);
}

//react to users keyboard input
void handleKeyboard(unsigned char key, int _x, int _y) {
    //CALL GLOBAL VARIABLES
    //::reset;

    //close window
    if (key == 'q' or key == 'Q') {
        exit(0);
    }
    //reset simulation
    if (key == 'r' or key == 'R') {
        reset=true;
    }
    if (key == ' '){
        cout<<"shot"<<endl;
        shootPaintBall();
    }
}
void handleSpecialKeyboard(int key, int _x, int _y) {
    
    if(key==GLUT_KEY_LEFT){
        crossHairPos[0] = crossHairPos[0] - 0.05;
        cout<<"left"<<endl;
    }
    if(key==GLUT_KEY_RIGHT){
        crossHairPos[0] = crossHairPos[0] + 0.05;
        cout<<"right"<<endl;
    }
    if(key == GLUT_KEY_UP){
        crossHairPos[1] = crossHairPos[1] + 0.05;
        cout<<"up"<<endl;
    }
    if(key == GLUT_KEY_DOWN){
        crossHairPos[1] = crossHairPos[1] - 0.05;
        cout<<"down"<<endl;
    }
}

void OnMouseClick(int button, int state, int x, int y) {
    //shoot paintball
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cout<<"shot"<<endl;
        shootPaintBall();
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

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
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glShadeModel(GL_SMOOTH);
    projection();
    glutMouseFunc(OnMouseClick);
    glutKeyboardFunc(handleKeyboard);
    glutSpecialFunc(handleSpecialKeyboard);
    glutDisplayFunc(display);

    glutMainLoop();             //starts the event glutMainLoop

    return 0;

}
