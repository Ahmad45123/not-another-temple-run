#pragma once
#include <glut.h>

#include "util.h"

class Player
{
    vector<GroundInfo>* groundArray;

    public:
    float angle = 180.0;
    double curX = 0, curY = -0.03, curZ = -0.55;
    Direction curDirection = NEGATIVE_Z;

    double STEP_SIZE = 0.005;
    double LEAN_STEP_SIZE = 0.05;

    bool keys[256] = {};

    int curGround = 0;

    Player(vector<GroundInfo> *grounds) {
        groundArray = grounds;
    }

    Direction getRightDirection() {
        switch (curDirection) {
        case NEGATIVE_X:
            return NEGATIVE_Z;
            break;
        case POSITIVE_X:
            return POSITIVE_Z;
            break;
        case NEGATIVE_Z:
            return POSITIVE_X;
            break;
        case POSITIVE_Z:
            return NEGATIVE_X;
            break;
        }
    }

    Direction getLeftDirection() {
        switch (curDirection) {
        case NEGATIVE_X:
            return POSITIVE_Z;
            break;
        case POSITIVE_X:
            return NEGATIVE_Z;
            break;
        case NEGATIVE_Z:
            return NEGATIVE_X;
            break;
        case POSITIVE_Z:
            return POSITIVE_X;
            break;
        }
    }

    bool canTurn(Direction targetDirection) {
        int nextGround = (curGround + 1) % groundArray->size();
        if (groundArray->at(nextGround).dir == targetDirection) {
            double end = groundArray->at(curGround).endPos;
            cout << "end pos " << end << "\n";
            switch (curDirection) {
            case NEGATIVE_X:
                if (curX >= end && curX <= end + 0.2) return true;
                break;
            case POSITIVE_X:
                if (curX <= end && curX >= end - 0.2) return true;
                break;
            case NEGATIVE_Z:
                if (curZ >= end && curZ <= end + 0.2) return true;
                break;
            case POSITIVE_Z:
                if (curZ <= end && curZ >= end - 0.2) return true;
                break;
            }
        }
        return false;
    }

    void leanRight() {
        double center = groundArray->at(curGround).centerPos;
        switch (curDirection) {
        case NEGATIVE_X: 
            if (curZ - LEAN_STEP_SIZE > center - 0.1) curZ -= LEAN_STEP_SIZE;
            break;
        case POSITIVE_X:
            if (curZ + LEAN_STEP_SIZE < center + 0.1) curZ += LEAN_STEP_SIZE;
            break;
        case NEGATIVE_Z:
            if (curX + LEAN_STEP_SIZE < center + 0.1) curX += LEAN_STEP_SIZE;
            break;
        case POSITIVE_Z:
            if (curX - LEAN_STEP_SIZE > center - 0.1) curX -= LEAN_STEP_SIZE;
            break;
        }
    }

    void leanLeft() {
        double center = groundArray->at(curGround).centerPos;
        switch (curDirection) {
        case POSITIVE_X:
            if (curZ - LEAN_STEP_SIZE > center - 0.1) curZ -= LEAN_STEP_SIZE;
            break;
        case NEGATIVE_X:
            if (curZ + LEAN_STEP_SIZE < center + 0.1) curZ += LEAN_STEP_SIZE;
            break;
        case POSITIVE_Z:
            if (curX + LEAN_STEP_SIZE < center + 0.1) curX += LEAN_STEP_SIZE;
            break;
        case NEGATIVE_Z:
            if (curX - LEAN_STEP_SIZE > center - 0.1) curX -= LEAN_STEP_SIZE;
            break;
        }
    }

    void gotoNextGround() {
        curGround = (curGround + 1) % groundArray->size();
    }

    void keyDown(char c) {
        if (!keys['a'] && c == 'a' && canTurn(getLeftDirection())) {
            angle += 90;
            curDirection = getLeftDirection();
            gotoNextGround();
        }

        if (!keys['d'] && c == 'd' && canTurn(getRightDirection())) {
            angle -= 90;
            curDirection = getRightDirection();
            gotoNextGround();
        }

        if (!keys['m'] && c == 'm') {
            leanRight();
        }
        
        if (!keys['n'] && c == 'n') {
            leanLeft();
        }

        keys[c] = true;
    }

    void keyUp(char c) {
        keys[c] = false;
    }

    void tick() {
        int nextGround = (curGround + 1) % groundArray->size();
        Direction nxtGroundDir = groundArray->at(nextGround).dir;

        double curGroundEnd = groundArray->at(curGround).endPos;

        switch (curDirection) {
        case NEGATIVE_X:
            curX -= STEP_SIZE;
            if (nxtGroundDir == curDirection && curX <= curGroundEnd) gotoNextGround();
            if (nxtGroundDir != curDirection && curX < curGroundEnd) {
                STEP_SIZE = 0;
            }
            break;
        case POSITIVE_X:
            curX += STEP_SIZE;
            if (nxtGroundDir == curDirection && curX >= curGroundEnd) gotoNextGround();
            if (nxtGroundDir != curDirection && curX > curGroundEnd) {
                STEP_SIZE = 0;
            }
            break;
        case NEGATIVE_Z:
            curZ -= STEP_SIZE;
            if (nxtGroundDir == curDirection && curZ <= curGroundEnd) gotoNextGround();
            if(nxtGroundDir != curDirection && curZ < curGroundEnd) {
                STEP_SIZE = 0;
            }
            break;
        case POSITIVE_Z:
            curZ += STEP_SIZE;
            if (nxtGroundDir == curDirection && curZ >= curGroundEnd) gotoNextGround();
            if(nxtGroundDir != curDirection && curZ > curGroundEnd) {
                STEP_SIZE = 0;
            }
            break;
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

