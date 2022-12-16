#pragma once
#include <glut.h>

#include "util.h"

class Player
{
    public:
    float angle = 180.0;
    double curX = 0, curY = -0.05, curZ = -0.55;
    Direction curDirection = NEGATIVE_Z;
    double STEP_SIZE = 0.003;

    bool keys[256] = {};

    void keyDown(char c) {
        if (!keys['a'] && c == 'a') {
            angle += 90;
            switch (curDirection) {
            case NEGATIVE_X:
                curDirection = POSITIVE_Z;
                break;
            case POSITIVE_X:
                curDirection = NEGATIVE_Z;
                break;
            case NEGATIVE_Z:
                curDirection = NEGATIVE_X;
                break;
            case POSITIVE_Z:
                curDirection = POSITIVE_X;
                break;
            }
        }

        if (!keys['d'] && c == 'd') {
            angle -= 90;
            switch (curDirection) {
            case NEGATIVE_X:
                curDirection = NEGATIVE_Z;
                break;
            case POSITIVE_X:
                curDirection = POSITIVE_Z;
                break;
            case NEGATIVE_Z:
                curDirection = POSITIVE_X;
                break;
            case POSITIVE_Z:
                curDirection = NEGATIVE_X;
                break;
            }
        }

        keys[c] = true;
    }

    void keyUp(char c) {
        keys[c] = false;
    }

    void tick() {
        if (keys['w']) {
            switch (curDirection) {
            case NEGATIVE_X:
                curX -= 0.01;
                break;
            case POSITIVE_X:
                curX += 0.01;
                break;
            case NEGATIVE_Z:
                curZ -= 0.01;
                break;
            case POSITIVE_Z:
                curZ += 0.01;
                break;
            }
        }
    }

    void draw() {
        glPushMatrix();
        glTranslated(curX, curY, curZ);
        glRotated(angle, 0, 1, 0);

        // Face
        glPushMatrix();
        glTranslated(0, 0.095, 0);
        glColor3f(0.88, 0.67, 0.41);
        glutSolidSphere(0.01, 50, 50);
        glPopMatrix();

        // Body
        glPushMatrix();
        glTranslated(0, 0.07, 0);
        glScaled(2.5, 3.5, 1.5);
        glColor3f(1, 0, 0);
        glutSolidCube(0.01f);
        glPopMatrix();

        // arm one
        glPushMatrix();
        glTranslated(0.015, 0.075, 0);
        glScaled(0.5, 1.5, 0.5);
        glColor3f(0.88, 0.67, 0.41);
        glutSolidCube(0.01f);
        glPopMatrix();

        // arm two
        glPushMatrix();
        glTranslated(-0.015, 0.075, 0);
        glScaled(0.5, 1.5, 0.5);
        glColor3f(0.88, 0.67, 0.41);
        glutSolidCube(0.01f);
        glPopMatrix();

        // eyes
        glPushMatrix();
        glTranslated(-0.005, 0.099, 0.009);
        glColor3f(0, 0, 0);
        glutSolidSphere(0.001, 50, 50);
        glPopMatrix();

        // eyes 2
        glPushMatrix();
        glTranslated(0.005, 0.099, 0.009);
        glColor3f(0, 0, 0);
        glutSolidSphere(0.001, 50, 50);
        glPopMatrix();

        glPopMatrix();
    }
};

