#include "Player.h"

#include <glut.h>

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

void Player::gotoNextGround() {
    curGround = (curGround + 1) % groundArray->size();
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

    if (!keys['m'] && c == 'm') {
        leanRight();
    }

    if (!keys['n'] && c == 'n') {
        leanLeft();
    }

    keys[c] = true;
}

void Player::keyUp(char c) {
    keys[c] = false;
}

void Player::tick() {
    int nextGround = (curGround + 1) % groundArray->size();
    Direction nxtGroundDir = groundArray->at(nextGround).dir;

    double curGroundEnd = groundArray->at(curGround).endPos;

    switch (curDirection) {
    case NEGATIVE_X:
        curX -= STEP_SIZE;
		playerModel.pos.x -= STEP_SIZE; // TODO
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
        if (nxtGroundDir != curDirection && curZ < curGroundEnd) {
            STEP_SIZE = 0;
        }
        break;
    case POSITIVE_Z:
        curZ += STEP_SIZE;
        if (nxtGroundDir == curDirection && curZ >= curGroundEnd) gotoNextGround();
        if (nxtGroundDir != curDirection && curZ > curGroundEnd) {
            STEP_SIZE = 0;
        }
        break;
    }
}

void Player::draw() {
    playerModel.Draw();
	playerModel.rot.y = angle;
	playerModel.pos.x = curX;
    playerModel.pos.z = curZ;
}
