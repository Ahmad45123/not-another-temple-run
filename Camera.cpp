#include "math.h"
#include <glut.h>

namespace Camera {

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

    void tick() {
        static float fraction = 0.01f;

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
            curCameraY += 0.01;
        }
        if (keys['l']) {
            curCameraY -= 0.01;
        }

        if (keys['o']) {
            curCenterY += 0.01;
        }
        if (keys['k']) {
            curCenterY -= 0.01;
        }

        if (keys['t']) {
            lx = 0;
            lz = -1;
            x = 0;
            z = 0.43;
            curCameraY = 1.4;
            curCenterY = -0.57;
        }

        if (keys['s']) {
            lx = 0;
            lz = -1;
            x = 0;
            z = 0.849999547;
            curCameraY = 0.1;
            curCenterY = 0.089999999999999983;
        }

        if (keys['f']) {
            lx = -0.999941707;
            lz = -0.0107973665;
            x = 1.04136741;
            z = -0.00670977216;
            curCameraY = 0.28000000000000014;
            curCenterY = 0.089999999999999983;
        }
    }

    void draw() {
        gluLookAt(x, curCameraY, z,
            x + lx, curCenterY, z + lz,
            0.0f, 1.0f, 0.0f);
    }
}