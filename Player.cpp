#include "Player.h"

#include <glut.h>
#include <iostream>

extern GameStatus gameStatus;

Direction Player::getRightDirection() {
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
    return UNKNOWN;
}

Direction Player::getLeftDirection() {
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
    return UNKNOWN;
}

bool Player::canTurn(Direction targetDirection) {
    int nextGround = (curGround + 1) % groundArray->size();
    if (groundArray->at(nextGround).dir == targetDirection) {
        double end = groundArray->at(curGround).endPos;
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

void Player::leanRight() {
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

void Player::leanLeft() {
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

void Player::rotatePlayer() {
    switch (curDirection) {
    case NEGATIVE_X:
        playerModel.rot.x = 90;
        playerModel.rot.y = 0;
        playerModel.rot.z = 90;
        break;
    case POSITIVE_X:
        playerModel.rot.x = 90;
        playerModel.rot.y = 0;
        playerModel.rot.z = 270;
        break;
    case NEGATIVE_Z:
        playerModel.rot.x = 270;
        playerModel.rot.y = 180;
        playerModel.rot.z = 0;
        break;
    case POSITIVE_Z:
        playerModel.rot.x = 90;
        playerModel.rot.y = 0;
        playerModel.rot.z = 0;
        break;
    }
}

void Player::gotoNextGround() {
    curGround = (curGround + 1) % groundArray->size();
    STEP_SIZE *= 1.05;
}

void Player::keyDown(char c) {
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

    if (!keys[' '] && c == ' ' && !goingUp && curHeight == 0) {
        util::playSound("sounds/jump.wav");
        goingUp = true;
    }

    keys[c] = true;
}

void Player::keyUp(char c) {
    keys[c] = false;
}

void Player::specialKeyDown(int c) {
    if (!specialKeys[GLUT_KEY_RIGHT] && c == GLUT_KEY_RIGHT) {
        leanRight();
    }

    if (!specialKeys[GLUT_KEY_LEFT] && c == GLUT_KEY_LEFT) {
        leanLeft();
    }

    specialKeys[c] = true;
}

void Player::specialKeyUp(int c) {
    specialKeys[c] = false;
}

extern Gamemode gameMode;
extern int gameTime;

void Player::tick() {
    int nextGround = (curGround + 1) % groundArray->size();
    Direction nxtGroundDir = groundArray->at(nextGround).dir;

    double curGroundEnd = groundArray->at(curGround).endPos;

    switch (curDirection) {
    case NEGATIVE_X:
        curX -= STEP_SIZE;
        if (nxtGroundDir == curDirection && curX <= curGroundEnd) gotoNextGround();
        if (nxtGroundDir != curDirection && curX < curGroundEnd) {
            fall();
        }
        break;
    case POSITIVE_X:
        curX += STEP_SIZE;
        if (nxtGroundDir == curDirection && curX >= curGroundEnd) gotoNextGround();
        if (nxtGroundDir != curDirection && curX > curGroundEnd) {
            fall();
        }
        break;
    case NEGATIVE_Z:
        curZ -= STEP_SIZE;
        if (nxtGroundDir == curDirection && curZ <= curGroundEnd) gotoNextGround();
        if (nxtGroundDir != curDirection && curZ < curGroundEnd) {
            fall();
        }
        break;
    case POSITIVE_Z:
        curZ += STEP_SIZE;
        if (nxtGroundDir == curDirection && curZ >= curGroundEnd) gotoNextGround();
        if (nxtGroundDir != curDirection && curZ > curGroundEnd) {
            fall();
        }
        break;
    }

    // Handle Jump
    if (goingUp) {
        curJumpStep *= 1.15;
        curHeight += curJumpStep;
        if (curHeight >= maxHeight) {
            goingUp = false;
        }
    }
    else if (curHeight > 0) {
        curHeight -= curJumpStep;
        curJumpStep /= 1.15;
        if (curHeight <= 0) curHeight = 0;
    }
    
    if (isFalling) {
		curHeight -= curJumpStep;
        curJumpStep *= 1.15;
        if (curHeight < -20000) {
            glutHideWindow();
            std::cout << "\x1B[2J\x1B[H";
            gameStatus = LOST;

            if (gameMode == ROCK) {
				util::showMessageBox("You collected " + std::to_string(this->coins) + " coins!");
            }
            else {
                util::showMessageBox("You scored " + std::to_string(gameTime) + "!");
            }
        }
    }
}

void Player::draw() {
    glPushMatrix();
    if (this->shieldRemainingTime > 0) {
        glColor3f(0.0, 1.1 - (this->shieldRemainingTime / 5.0 * 1.0), 0.0);
    }
    playerModel.Draw();
	glPopMatrix();
    rotatePlayer();
	playerModel.pos.x = curX;
    playerModel.pos.z = curZ;
    playerModel.pos.y = curY + curHeight;
}

void Player::fall() {
    if (isFalling) return;
    isFalling = true;
    util::playSound("sounds/fall.wav");
}

extern int WIDTH;
void Player::motionFunc(int x, int y) {
    if (gameStatus != PLAYING || groundArray->size() == 0) return;
        
    double xLoc = x*1.0 / WIDTH;
    double pos = 0.2 * xLoc - 0.1;
    
    double center = groundArray->at(curGround).centerPos; // [center - 0.1, center + 0.1]
    switch (curDirection) {
    case NEGATIVE_X: 
        curZ = center - pos;
        break;
    case POSITIVE_X:
        curZ = center + pos;
        break;
    case NEGATIVE_Z:
        curX = center + pos;
        break;
    case POSITIVE_Z:
        curX = center - pos;
        break;
    }
}

int prevMouseState = GLUT_UP;
void Player::mouseFunc(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
		if (GLUT_DOWN != prevMouseState && state == GLUT_DOWN && !goingUp && curHeight == 0) {
            util::playSound("sounds/jump.wav");
            goingUp = true;
		}
        prevMouseState = state;
    }
}