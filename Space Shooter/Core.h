#ifndef Core_h
#define Core_h

#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define SCREEN_WIDTH 600    
#define SCREEN_HEIGHT 800

//get all available keys
bool keys[GLFW_KEY_LAST] = { false };

//for funni circles
float theta;

//our good old friend
static float deltaTime;

void keycallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Update the key state when pressed or released
    if (action == GLFW_PRESS)
    {
        keys[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        keys[key] = false;
    }
}

//handling x y values
class Vector2D {   
public:
    float x, y;

    //create at specific location
    Vector2D(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y){}

    //set specific x,y values
    void setValues(float _x, float _y) 
    {
        x = _x;
        y = _y;
    }

    //set values based on another Vector2D class
    void setValues(const Vector2D* v) 
    {
        x = v->x;
        y = v->y;
    }

    //check if this Vector2D matches another
    bool matches(const Vector2D* v) 
    {
        return ((x == v->x) && (y == v->y)) ? true : false;
    }

    //check if this position matches a specified set of x and y values
    bool matches(float _x, float _y) 
    {
        return ((x == _x) && (y == _y)) ? true : false;
    }

    //faster than getMagnitude() where applicable
    float getSquaredMagnitude() 
    {
        return x * x + y * y;
    }

    float getMagnitude() 
    {
        return hypot(x, y);
    }

    //get angle of this vector in radians
    float getAngleRadians() 
    {
        return atan2(y, x);
    }

    //get angle of this vector in degrees
    float getAngleDegrees() 
    {
        return (getAngleRadians() / 3.14159) * 180.0f;
    }

    //set normalized values based on angle
    void setValuesFromAngle(float angle) 
    {
        x = sin(angle);
        y = cos(angle);
    }

    //normalize this vector
    void normalize() {
        float magnitude = getMagnitude();
        if (magnitude != 0) {
            x /= magnitude;
            y /= magnitude;
        }
        else {
            x = 0;
            y = 0;
        }
    }
};

#endif