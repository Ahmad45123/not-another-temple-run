#pragma once

#include "Camera.h"

class FreeCamera : public Camera
{
    float angle = 0.0;
    float lx = 0.0f, lz = -1.0f;
    float x = 0.0f, z = 0.2f;
    double curCameraY = 0.1;
    double curCenterY = -0.1;
    bool keys[256] = {};
    bool specialKeys[256] = {};

public:
    virtual void keyDown(int c) {
        keys[c] = true;
    }

    virtual void keyUp(int c) {
        keys[c] = false;
    }

    virtual void specialKeyDown(int c) {
        specialKeys[c] = true;
    }

    virtual void specialKeyUp(int c) {
        specialKeys[c] = false;
    }

    virtual void tick();
    virtual void draw();
};

