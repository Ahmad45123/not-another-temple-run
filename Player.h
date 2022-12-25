#pragma once
#include <vector>
#include "Model_3DS.h"

#include "util.h"

class Player
{
    public:
    std::vector<GroundInfo>* groundArray;

    float angle = 180.0f;
    double curX = 0, curY = 0.02, curZ = -0.55;
    Direction curDirection = NEGATIVE_Z;

    double STEP_SIZE = 0.005;
    double LEAN_STEP_SIZE = 0.05;

    bool keys[256] = {};
    bool specialKeys[256] = {};

    int curGround = 0;
    
    bool goingUp = false;
    bool isFalling = false;
    double curHeight = 0;
    double maxHeight = 0.07;
    double curJumpStep = 0.0001;

    int coins = 0;
    bool gotShield = false;
		
	Model_3DS playerModel = Model_3DS(curX, curY, curZ, 0.0005, 0.0005, 0.0005, 270, 0, 0);
	
    Player(std::vector<GroundInfo> *grounds) {
		playerModel.Load("models/player/Male1.3ds");
        groundArray = grounds;
    }

    Direction getRightDirection();
    Direction getLeftDirection();
    bool canTurn(Direction targetDirection);

    void leanRight();
    void leanLeft();

    void gotoNextGround();
    void fall();

    void keyDown(char c);
    void keyUp(char c);
    void specialKeyDown(int c);
    void specialKeyUp(int c);

    void tick();
    void draw();
};

