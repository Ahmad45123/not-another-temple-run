#pragma once

class Camera
{
    float angle = 0.0;
    float lx = 0.0f, lz = -1.0f;
    float x = 0.0f, z = 0.2f;
    double curCameraY = 0.1;
    double curCenterY = -0.1;
    bool keys[256] = {};
    bool specialKeys[256] = {};

public:
    void keyDown(int c) {
        keys[c] = true;
    }

    void keyUp(int c) {
        keys[c] = false;
    }

    void specialKeyDown(int c) {
        specialKeys[c] = true;
    }

    void specialKeyUp(int c) {
        specialKeys[c] = false;
    }

    void tick();
    void draw();
};

