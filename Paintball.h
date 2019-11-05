#ifndef PAINTBALL_H
#define PAINTBALL_H

class Paintball {
public:
    Paintball();
    Paintball(float inX, float inY, float inZ, int inSize);
    float mX;
    float mY;
    float mZ;
    float color[3];
    float size;
    float dX;
    float dY;
    float dZ;
    int material;
    float speed;
};

#endif