#include "Camera.h"

#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include <iostream>

void Camera::tick() {
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

void Camera::draw() {
    gluLookAt(x, curCameraY, z,
        x + lx, curCenterY, z + lz,
        0.0f, 1.0f, 0.0f);
}
