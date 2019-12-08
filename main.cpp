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
#include <stdio.h>
#include <stdlib.h>

// //music
// #include <Windows.h>
// #include <MMSystem.h>

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

//texture variables
GLubyte* grass_img;
GLubyte* wood_img;
GLubyte* brick_img;
GLubyte* splat;
//an array for iamge data
GLuint textures[4];

//dimensions of textures
int width1, height1, max1;
int width2, height2, max2;
int width3, height3, max3;
int width4, height4, max4;

float cols[6][3] = { {1,0,0}, {1,1,1}, {1,1,0}, {0,1,0}, {0,0,1}, {1,0,1} };
float floorText[4][2] = { {0,0}, {0,1}, {1,1}, {1,0} };

//global variables
std::vector<Paintball> paintBallVec(0);
std::vector<Splatter> splatterVec(0);
//bool shot = false;
int cnt = 0;

//toggles
bool reset = true;
bool axisToggle = false;
bool pauseToggle = true;
//false = mouse, true = arrowKey
//maybe change the default to mouse later****
bool keyboardMouseToggle = true;

//total shots fired
float shotsFired=0;

//crosshair coordinates
float crossHairPos[3] = {0, 9, 47};

// One light for now
float lightPos[2][4] = {
    { 0, 20, 0, 1 },
    { -5, 20, 0, 1 }
};

//camera position
float eye[3] = {0, 10, 50};

//some basic lighting characteristics
float amb[4] = {0,0,0,0};
float spec[4] = {1,1,1,1};
float diff[4] = {1,1,1,1};

//Floor map coordinates
float floorCoord[4][3]={
    {-20, 0, -40},
    {20, 0, -40},
    {20, 0, 40},
    {-20, 0, 40}
};

float wallCoords[4][3]={
    {-15, 0, -35},
    {-15, 20, -35},
    {15, 20, -35},
    {15, 0, -35},
};

float tableCoords[4][3]={
    {-8, 7, 42},
    {8, 7, 42},
    {8, 7, 49},
    {-8, 7, 49}
};

//colour change
bool colourChanged = false;
float paintBallColour[3]={0,0,0};

//material variables
GLfloat materialAmbient[4] = {0,0,0,1};
GLfloat materialSpecular[4] = {.5,.5,.5,1};
GLfloat materialDiffuse[4] = {1,0,0,0};
GLfloat materialShininess[] = {10.0};

//this function is called once at the beginning of the program to print instructions for user
void instructions() {
  cout<<endl<<"WELCOME TO 3D PAINTBALL SIMULATOR" <<endl;
  cout<<"======================================="<<endl;
  cout<<"q : quit simulation"<<endl;
  cout<<"c : switch between keyboard and mouse controls"<<endl;
}

//controls for mouse mode
void mouseControls() {
    cout <<endl<< "Mouse Controls : " << endl;
    cout<<"---------------------------------------"<<endl;
    cout << "Control crosshair with mouse position" << endl;
    cout << "Move player with 'a' (left) and 'd' (right)" << endl;
    cout << "Right click for menu options" << endl;
    cout << "Left click to shoot paintball" << endl;
    cout<<"c : switch between mouse or arrow keys for cursor position"<<endl;
}

//controls for keyboard mode
void keyboardControls() {
    cout<<endl<<"Keyboard Controls : "<<endl;
    cout<<"---------------------------------------"<<endl;
    cout<<"space : shoot paintball"<<endl;
    cout<<"r : turn paintballs red"<<endl;
    cout<<"g : turn paintballs green"<<endl;
    cout<<"b : turn paintballs blue"<<endl;
    cout<<"w : turn paintballs to random colours"<<endl;
    cout<<"Move player with 'a' (left) and 'd' (right)"<<endl;
    cout<<"c : switch between mouse or arrow keys for cursor position"<<endl;
}

//menu actions/procedure
void menuProc(int value){
    if (value == 1) {
        cout << "Paintball color switched to red!" << endl;
        paintBallColour[0]=1;
        paintBallColour[1]=0;
        paintBallColour[2]=0;
        colourChanged=true;
    }
    if (value == 2) {
        cout << "Paintball color switched to green!" << endl;
        paintBallColour[0]=0;
        paintBallColour[1]=1;
        paintBallColour[2]=0;
        colourChanged=true;
    }
    if (value == 3) {
        cout << "Paintball color switched to blue!" << endl;
        paintBallColour[0]=0;
        paintBallColour[1]=0;
        paintBallColour[2]=1;
        colourChanged=true;
    }
    if (value == 4) {
        cout << "Paitball color switched to randomize!" << endl;
        colourChanged=false;
    }
}

//menu for ball selection related to mouse controls
void createMenu(){
    int main_id = glutCreateMenu(menuProc);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Random", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}



//Draw the floor in the simulation
void floor(){
    //define materials
    GLfloat dummaterialDiffFloor[4]={0.2, 0.8, 0.4, 1.0};
    GLfloat dummaterialSpecFloor[4] = {0.0, 0.0, 0.0, 1.0};
    GLfloat dummaterialAmbFloor[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat dummaterialShinyFloor = 10.0;
    GLfloat materialEmit[4]={0,0,0,0};

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmit);
    //set material properties
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dummaterialDiffFloor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, dummaterialAmbFloor);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, dummaterialShinyFloor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, dummaterialSpecFloor);

    //draw floor
    //here
    // glColor3fv(cols[1]);
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    glBegin(GL_POLYGON);
    glNormal3f(0.0,1.0,0.0);

    for(int i=0;i<4;i++){
        glTexCoord2f(floorText[i][0],floorText[i][1]);
        glVertex3f(floorCoord[i][0],floorCoord[i][1],floorCoord[i][2]);
    }
    glEnd();

}

//Draw the wall which will be shot at
void wall() {
    GLfloat dummaterialDiffWall[4]={0.5, 0.2, 0.0, 0.0};
    GLfloat dummaterialSpecWall[4] = {0, 0, 0, 0};
    GLfloat dummaterialAmbWall[4] = {1.0, 1.0, 1.0, 0};
    GLfloat dummaterialShinyWall = 4.0;
    GLfloat materialEmit[4]={0,0,0,0};

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmit);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dummaterialDiffWall);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, dummaterialAmbWall);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, dummaterialShinyWall);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, dummaterialSpecWall);

    //here
    // glColor3fv(cols[1]);
    glBindTexture(GL_TEXTURE_2D, textures[2]);

    glBegin(GL_QUADS);
        glNormal3f(0.0,0.0,1.0);
        for(int i=0;i<4;i++){
            glTexCoord2f(floorText[i][0],floorText[i][1]);
            glVertex3f(wallCoords[i][0], wallCoords[i][1], wallCoords[i][2]);
        }
    glEnd();
}

//Draw a table which the shooter stands behind
void drawTable() {
    //initializing materialsßßß
    GLfloat dummaterialDiffTable[3]={0.9,0.6,0.3};
    GLfloat dummaterialSpecTable[4] = {0,0,0,0};
    GLfloat dummaterialAmbTable[4] = {1,1,1,0};
    GLfloat dummaterialShinyTable = 4;
    GLfloat emitTable[4]={0,0,0,0};

    GLfloat ballDiff1[3]={1,0,0};
    GLfloat ballDiff2[3]={0,1,0};
    GLfloat ballDiff3[3]={0,0,1};
    GLfloat ballEmit[4]={1,0,0,1};
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dummaterialDiffTable);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, dummaterialAmbTable);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, dummaterialShinyTable);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, dummaterialSpecTable);
    glMaterialfv(GL_FRONT, GL_EMISSION, emitTable);

    
    // glColor3fv(cols[1]);
    //glBindTexture(GL_TEXTURE_2D, textures[1]);

    glBegin(GL_POLYGON);
    glNormal3f(0,1.0,0);
        for(int i=0;i<4;i++){
            glTexCoord2f(floorText[i][0],floorText[i][1]);
            glVertex3f(tableCoords[i][0],tableCoords[i][1],tableCoords[i][2]);
        }
    glEnd();

    //make selected ball on table glow
    glPushMatrix();

        //red ball
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ballDiff1);
        glTranslatef(-2,7.25,42.5);
        if(paintBallColour[0]==1 and colourChanged){glMaterialfv(GL_FRONT, GL_EMISSION, ballEmit);}
        else{glMaterialfv(GL_FRONT, GL_EMISSION, emitTable);}
        glutSolidSphere(.25, 7, 70);
    glPopMatrix();
    glPushMatrix();
        //green ball
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ballDiff2);
        if(paintBallColour[1]==1 and colourChanged){glMaterialfv(GL_FRONT, GL_EMISSION, ballEmit);}
        else{glMaterialfv(GL_FRONT, GL_EMISSION, emitTable);}
        glTranslatef(0,7.25,42.5);
        glutSolidSphere(.25, 7, 70);
    glPopMatrix();
    glPushMatrix();
        //blue ball
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ballDiff3);
        if(paintBallColour[2]==1 and colourChanged){glMaterialfv(GL_FRONT, GL_EMISSION, ballEmit);}
        else{glMaterialfv(GL_FRONT, GL_EMISSION, emitTable);}
        glTranslatef(2,7.25,42.5);
        glutSolidSphere(.25, 7, 70);
    glPopMatrix();
}

//draw x,y,z axis, useful for perspective and testing (OPTIONAL)
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
    GLfloat dummaterialDiffCrossHair[4]={1,0,0,0};
    GLfloat materialEmit[4]={0,0,0,1};
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmit);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dummaterialDiffCrossHair);

    glBegin(GL_LINES);
        glVertex3f(crossHairPos[0] - 0.1, crossHairPos[1], crossHairPos[2]);
        glVertex3f(crossHairPos[0] + 0.1, crossHairPos[1], crossHairPos[2]);

        glVertex3f(crossHairPos[0], crossHairPos[1] + 0.1, crossHairPos[2]);
        glVertex3f(crossHairPos[0], crossHairPos[1] - 0.1, crossHairPos[2]);
    glEnd();

    //draw circle around cross
    int segments=100;
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < segments; i++)
    {   
        //calculate angle
        float theta = 2.0f * 3.1415926f * float(i) / segments;
        float r=.1;
        //calculate coordinates
        float x = r * cosf(theta)+crossHairPos[0];
        float y = r * sinf(theta)+crossHairPos[1];
        float z=crossHairPos[2];

        glVertex3f(x , y ,z);//output vertex
    }
    glEnd();
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < segments; i++)
    {
        //calculate angle
        float theta = 2.0f * 3.1415926f * float(i) / segments;
        float r=.12;
        //calculate coordinates
        float x = r * cosf(theta)+crossHairPos[0];
        float y = r * sinf(theta)+crossHairPos[1];
        float z=crossHairPos[2];

        glVertex3f(x ,y ,z); //output vertex
    }
    glEnd();
}

//draw splatters on wall
void drawSplatters() {
    GLfloat dummaterialDiffSplatter[4]={0.5, 0.2, 0.0, 1.0};
    GLfloat dummaterialSpecSplatter[4]={0.0, 0.0, 0.0, 1.0};
    GLfloat dummaterialAmbSplatter[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat dummaterialShinySplatter = 4.0;
    
    for(int i =0; i< splatterVec.size(); i++) { 
        GLfloat dummaterialDiffSplatter[4]={1,1,1,0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dummaterialDiffSplatter);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, dummaterialAmbSplatter);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, dummaterialShinySplatter);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, dummaterialSpecSplatter);

        //uncomment for splatters
        glColor3fv(cols[1]);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindTexture(GL_TEXTURE_2D, textures[3]);       

        glBegin(GL_QUADS);
            glNormal3f(0.0,0.0,1.0);
            glTexCoord2f(floorText[0][0],floorText[0][1]);
            glVertex3f(splatterVec[i].mX - 2, splatterVec[i].mY - 2, -34.9);
            glTexCoord2f(floorText[1][0],floorText[1][1]);
            glVertex3f(splatterVec[i].mX - 2, splatterVec[i].mY + 2, -34.9);
            glTexCoord2f(floorText[2][0],floorText[2][1]);
            glVertex3f(splatterVec[i].mX + 2, splatterVec[i].mY + 2, -34.9);
            glTexCoord2f(floorText[3][0],floorText[3][1]);
            glVertex3f(splatterVec[i].mX + 2, splatterVec[i].mY - 2, -34.9);
        glEnd();
    }
}

//add to vector of splatters and remove from paintball vector, parameter is index of paintball vector for current hit
void wallInteraction(int p) {
    Splatter S(paintBallVec[p].mX, paintBallVec[p].mY, paintBallVec[p].color);   //create new 'splatter'
    splatterVec.push_back(S);
    paintBallVec.erase(paintBallVec.begin()+p); //remove paintball
}

//shooting a paintball ads it to the vector
void shootPaintBall(){
    shotsFired+=1;
    Paintball P(crossHairPos[0], crossHairPos[1], crossHairPos[2]);
    if(colourChanged){
            P.color[0]=paintBallColour[0];
            P.color[1]=paintBallColour[1];
            P.color[2]=paintBallColour[2];
    }
    paintBallVec.push_back(P);
}

//increment z value of all active paintballs
void drawPaintBalls(){
    //declare materials
    GLfloat dummaterialDiffBall[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat dummaterialSpecBall[4] = {0.0, 0.0, 0.0, 1.0};
    GLfloat dummaterialAmbBall[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat dummaterialShinyBall = 2.0;
    for(int i = 0; i < paintBallVec.size(); i++){
        if(colourChanged){
            dummaterialDiffBall[0]=paintBallColour[0];
            dummaterialDiffBall[1]=paintBallColour[1];
            dummaterialDiffBall[2]=paintBallColour[2];
        }else{
            dummaterialDiffBall[0]=paintBallVec[i].color[0];
            dummaterialDiffBall[1]=paintBallVec[i].color[1];
            dummaterialDiffBall[2]=paintBallVec[i].color[2];
        }

        glPushMatrix();
            //set materials
            glMaterialfv(GL_FRONT, GL_DIFFUSE, dummaterialDiffBall);
            glMaterialfv(GL_FRONT, GL_AMBIENT, dummaterialAmbBall);
            glMaterialf(GL_FRONT, GL_SHININESS, dummaterialShinyBall);
            glMaterialfv(GL_FRONT, GL_SPECULAR, dummaterialSpecBall);
        
            paintBallVec[i].mZ = paintBallVec[i].mZ - paintBallVec[i].speed;    //"-" because shooting 'down' range
            
            //altering height of paintball
            //increase heigtht to maximum of 14, then decrease height till it hits the wall
            if(paintBallVec[i].mY<14){
                if(paintBallVec[i].mY>12){
                    paintBallVec[i].mY +=.05;
                }else{
                    paintBallVec[i].mY +=.1;
                }
                
            }else{
                if(paintBallVec[i].mY <12){
                    paintBallVec[i].mY -= .1;
                }else{
                    paintBallVec[i].mY -= .2;
                }

            }

            glTranslatef(paintBallVec[i].mX, paintBallVec[i].mY, paintBallVec[i].mZ);

            if (paintBallVec[i].mZ <= -35 and paintBallVec[i].mX<15 
            and paintBallVec[i].mX>-15 and paintBallVec[i].mY<20 and paintBallVec[i].mY>0) {    //hit wall
                wallInteraction(i);
            }
            
            //if ball hits the floor
            if(paintBallVec[i].mY<=0){
                continue;
            }else{
                glutSolidSphere(1, 100, 100);
            }
            
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
        mouseControls();
        keyboardControls();
        reset = false;
    }

    //try to put the menu stuff in here
    //only create menu if in mouse control version, otherwise hotkeys for those actions
    if (keyboardMouseToggle == false) {
        createMenu();
    }

    for (unsigned int j = 0; j < 1; j++) {
        glLightfv(GL_LIGHT0 +j, GL_POSITION, lightPos[j]);
        glLightfv(GL_LIGHT0 +j, GL_AMBIENT, amb);
        glLightfv(GL_LIGHT0 +j, GL_DIFFUSE, diff);
        glLightfv(GL_LIGHT0 +j, GL_SPECULAR, spec);
    }   

    if (axisToggle == true){
        drawAxis();
    }

    //textDisplay();

    floor();

    wall();

    drawTable();

    drawCrossHair();

    drawPaintBalls();

    drawSplatters();

    //switch our buffers for a smooth animation
    glutSwapBuffers();

    //force a redisplay, to keep the animation running
    glutPostRedisplay();
}


//here - code taken from textures.cpp example
//taken from textures example
GLubyte* LoadPPM(char* file, int* width, int* height, int* maxi)
{
    GLubyte* img;
    FILE *fd;
    int n, m;
    int  k, nm;
    char c;
    int i;
    char b[100];
    float s;
    int red, green, blue;
    
    fd = fopen(file, "r");
    fscanf(fd,"%[^\n] ",b);
    if(b[0]!='P'|| b[1] != '3')
    {
        //printf("%s is not a PPM file!\n",file);
        exit(0);
    }
    //printf("%s is a PPM file\n", file);
    fscanf(fd, "%c",&c);
    while(c == '#')
    {
        fscanf(fd, "%[^\n] ", b);
        printf("%s\n",b);
        fscanf(fd, "%c",&c);
    }
    ungetc(c,fd);
    fscanf(fd, "%d %d %d", &n, &m, &k);
    
    //printf("%d rows  %d columns  maxi value= %d\n",n,m,k);
    
    nm = n*m;
    
    img = (GLubyte*)malloc(3*sizeof(GLuint)*nm);
    
    
    s=255.0/k;
    
    
    for(i=0;i<nm;i++)
    {
        fscanf(fd,"%d %d %d",&red, &green, &blue );
        img[3*nm-3*i-3]=red*s;
        img[3*nm-3*i-2]=green*s;
        img[3*nm-3*i-1]=blue*s;
    }
    
    *width = n;
    *height = m;
    *maxi = k;
    
    return img;
}

//here
//initialize textures
void init(void)
{
    
    glMatrixMode(GL_TEXTURE);
    glScalef(1,-1,-1);
    
    const char * grasschar="grass.ppm";
    grass_img = LoadPPM("grass.ppm", &width1, &height1, &max1); 
    wood_img = LoadPPM("wood.ppm", &width2, &height2, &max2);
    brick_img = LoadPPM("brick.ppm", &width3, &height3, &max3);
    splat = LoadPPM("rainbow.ppm", &width4, &height4, &max4); 
    
    glEnable(GL_TEXTURE_2D);
    
    glGenTextures(3, textures);
     // grass texture
    glBindTexture(GL_TEXTURE_2D, textures[0]);
   
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, grass_img);
    
    // // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP_TO_BORDER);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //wood texture
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, wood_img);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //brick texture
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width3, height3, 0, GL_RGB, GL_UNSIGNED_BYTE, brick_img);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // splatter texture
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width4, height4, 0, GL_RGB, GL_UNSIGNED_BYTE, splat);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    
    
    
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    
    //enable Z buffer test, otherwise things appear in the order they're drawn
    //enable lighting with 2 lights
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1,1,100);
    
    
}

//keyboard input actions
//Note: some actions only available when in keyboard mode (keyboardMouseToggle == true)
void handleKeyboard(unsigned char key, int _x, int _y) {

    //close window
    if (key == 'q' or key == 'Q') {
        exit(0);
    }
    //set paintballs to red
    if (keyboardMouseToggle) {
        if (key == 'r' or key == 'R') {
            cout << "Paitball color switched to red!" << endl; 
            paintBallColour[0]=1;
            paintBallColour[1]=0;
            paintBallColour[2]=0;
            colourChanged=true;
        }
    }
    //set paintballs to green
    if (keyboardMouseToggle) {
        if (key == 'g' or key == 'G') {
            cout << "Paitball color switched to green!" << endl; 
            paintBallColour[0]=0;
            paintBallColour[1]=1;
            paintBallColour[2]=0;
            colourChanged=true;
        }
    }
    //set paintballs to blue
    if (keyboardMouseToggle) {
        if (key == 'b' or key == 'B') {
            cout << "Paitball color switched to blue!" << endl; 
            paintBallColour[0]=0;
            paintBallColour[1]=0;
            paintBallColour[2]=1;
           colourChanged=true;
        }
    }
    //set paintballs back to random color
    if (keyboardMouseToggle) {
        if (key == 'w' or key == 'W') {
            cout << "Paitball color switched to randomize!" << endl; 
            colourChanged=false;
        }
    }
    //shootpaintball
    if (keyboardMouseToggle) {
        if (key == ' '){
            shootPaintBall();
        }
    }
    //toggle x, y, z axis display
    if (key == 'x' || key == 'X'){
        axisToggle = !axisToggle;
    }
    if (key == 'c' || key == 'C'){
        keyboardMouseToggle = !keyboardMouseToggle;
        if (keyboardMouseToggle == true) {
            //Note: crosshair remains at last location
            cout << "Switched to arrow-key controls!" << endl;
            // keyboardControls();
        } else {
            //Note: crosshair will jump to mouse position on fist movement
            cout << "Switched to mouse controls!" << endl;
            // mouseControls();
        }
    }

    //move character position
    //move left
    if (key == 'a' || key == 'A'){
        if (eye[0] >= -8) {
            eye[0] = eye[0] - 0.2;
            //keep cross Hair centered
            crossHairPos[0] = crossHairPos[0] - 0.2;
        }
    }
    //move right
    if (key == 'd' || key == 'D'){
        if (eye[0] <= 8) {
            eye[0] = eye[0] + 0.2;
            crossHairPos[0] = crossHairPos[0] + 0.2;
        }
    }
    //motion front and back might not be worth it but can try
    // if (key == 'w' || key == 'W'){
    //     //move forward (set a limit for how far can go)
    // }

}
void handleSpecialKeyboard(int key, int _x, int _y) {
    //crosshair position
    //Note: crosshair shouldnt move beyond field of view
    if (keyboardMouseToggle) {
        cout << "cross hair pos : " << crossHairPos[0] << " " << crossHairPos[1] << endl;
        if(key==GLUT_KEY_LEFT){
            if (crossHairPos[0] >= (eye[0] - 1)) {
                crossHairPos[0] = crossHairPos[0] - 0.05;
            }
        }
        if(key==GLUT_KEY_RIGHT){
            if (crossHairPos[0] <= (eye[0] + 1)) {
                crossHairPos[0] = crossHairPos[0] + 0.05;
            }
        }
        if(key == GLUT_KEY_UP){
            if (crossHairPos[1] <= (eye[1] + 1)) {
                crossHairPos[1] = crossHairPos[1] + 0.05;
            }
        }
        if(key == GLUT_KEY_DOWN){
            if (crossHairPos[1] >= (eye[1] - 1)) {
                crossHairPos[1] = crossHairPos[1] - 0.05;
            }
        }
    }
}

//In mouse mode, mouse left click shoots paintball
void OnMouseClick(int button, int state, int x, int y) {
    if (keyboardMouseToggle == false) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        //if (button == GLUT_LEFT_BUTTON) {
            shootPaintBall();
        }
    }
}

void motion(int x, int y) {
    if (keyboardMouseToggle == false) { 
        //only move crosshair within visible region
        //NOTE: change this to work for dynamic screensize somehow
        float ox = (float)(x)/250.0;
        float oy = (float)(y)/250.0;
        float adjX;
        float adjY;
        if (x <= 250) {
            adjX = (1.0 - ox);
            if (crossHairPos[0] >= eye[0] - 1) {
                crossHairPos[0] = eye[0] - adjX;
            }
        }
        if (x > 250) {
            adjX = ox - 1.0;
            if (crossHairPos[0] <= eye[0] + 1) {
                crossHairPos[0] = eye[0] + adjX;
            }
        }
        if (y <= 250) {
            adjY = (1.0 - oy);
            if (crossHairPos[1] <= eye[1] + 1) {
                crossHairPos[1] = eye[1] + adjY;
            }
        }
        if (y > 250) {
            adjY = -1.0 * (oy - 1.0);   //inverted y coordinate
            if (crossHairPos[1] >= eye[1] - 1) {
                crossHairPos[1] = eye[1] + adjY;    //due to invert add adjY instead
            }
        }
        //important notice about mouse controlled cursor :
        //occasionally cursor momentarily freezes at edges of window,
        //move mouse back into window view to fix
        
        //for debugging
        // cout << "x, y : " << x << " " << y << endl;
        // cout << "ox , oy : " << ox << " " << oy << endl;
        // cout << "adjX, adjY : " << adjX << " " << adjY << endl;

    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);     //starts up GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    //create window
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Paintball Range");  //creates the window
    
    
    
    //glEnable(GL_LIGHT1);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    glCullFace(GL_FRONT);

    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    init(); //here

    glutMouseFunc(OnMouseClick);
    glutKeyboardFunc(handleKeyboard);
    glutSpecialFunc(handleSpecialKeyboard);
    //glutMouseFunc(OnMouseClick);
    glutPassiveMotionFunc(motion);
    glutDisplayFunc(display);
    // PlaySound("35 - Lost Woods.wav", NULL, SND_SYNC);
    
    glutMainLoop();             //starts the event glutMainLoop

    return 0;

}
