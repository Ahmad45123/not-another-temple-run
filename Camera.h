#pragma once
#include <glut.h>
#include <math.h>
#include <iostream>

class Camera
{
public:
    float angle = 0.0;
    float lx = 0.0f, lz = -1.0f;
    float x = 0.0f, z = 0.2f;
    double curCameraY = 0.1;
    double curCenterY = -0.1;
    bool keys[256] = {};
    bool specialKeys[256] = {};

    void init() {

    }

    void keyDown(int c) {
        keys[c] = true;
        std::cout << x << " " << z << " " << curCameraY << " " << curCenterY << "\n";
    }

    void keyUp(int c) {
        keys[c] = false;
    }

    void specialKeyDown(int c) {
        specialKeys[c] = true;
        std::cout << x << " " << z << " " << curCameraY << " " << curCenterY << "\n";
    }

    void specialKeyUp(int c) {
        specialKeys[c] = false;
    }

    void tick() {
        static float fraction = 0.05f;

        if (specialKeys[GLUT_KEY_LEFT]) {
            angle -= 0.01f;
            lx = sin(angle);
            lz = -cos(angle);
        }
        if (specialKeys[GLUT_KEY_RIGHT]) {
            angle += 0.01f;
            lx = sin(angle);
            lz = -cos(angle);
        }
        if (specialKeys[GLUT_KEY_UP]) {
            x += lx * fraction;
            z += lz * fraction;
        }
        if (specialKeys[GLUT_KEY_DOWN]) {
            x -= lx * fraction;
            z -= lz * fraction;
        }

        if (keys['p']) {
            curCameraY += 0.05;
        }
        if (keys['l']) {
            curCameraY -= 0.05;
        }

        if (keys['o']) {
            curCenterY += 0.05;
        }
        if (keys['k']) {
            curCenterY -= 0.05;
        }
    }

    void draw() {
        gluLookAt(x, curCameraY, z,
            x + lx, curCenterY, z + lz,
            0.0f, 1.0f, 0.0f);
    }
};

