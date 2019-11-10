#ifndef SPLATTER_H
#define SPLATTER_H

//splatters will be random shapes created by Paintballs hitting the wall
class Splatter {
public:
	Splatter();
    Splatter(float inX, float inY);
    float mX;
    float mY;
    float color[3];
};

#endif