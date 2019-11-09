#ifndef PAINTBALL_H
#define PAINTBALL_H

class Paintball {
public:
    Paintball();
    Paintball(float inX, float inY, float inZ);
    float mX;
    float mY;
    float mZ;
    float color[3]; //maybe have a color and a material as well
    float size;
    float speed;
};

#endif