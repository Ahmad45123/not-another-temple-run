#pragma once
#include <vector>

#include "util.h"

class Player
{
    std::vector<GroundInfo>* groundArray;

    float angle = 180.0;
    double curX = 0, curY = -0.03, curZ = -0.55;
    Direction curDirection = NEGATIVE_Z;

    double STEP_SIZE = 0.005;
    double LEAN_STEP_SIZE = 0.05;

    bool keys[256] = {};

    int curGround = 0;

    public:
    Player(std::vector<GroundInfo> *grounds) {
        groundArray = grounds;
    }

    Direction getRightDirection();
    Direction getLeftDirection();
    bool canTurn(Direction targetDirection);

    void leanRight();
    void leanLeft();

    void gotoNextGround();

    void keyDown(char c);
    void keyUp(char c);

    void tick();
    void draw();
};

