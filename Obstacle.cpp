#include "Obstacle.h"

#include <iostream>
using namespace std;

Obstacle::Obstacle(Vector pos, Vector rot, Gamemode type, Player* pl) {
	position = pos;
	rotation = rot;
	player = pl;
	this->type = type;
	if (type == ROCK) {
		obstacleModel = new Model_3DS(position.x, position.y, position.z,
			0.001, 0.002, 0.001,
			rotation.x, rotation.y, rotation.z);
		obstacleModel->Load("models/rocks/Rock07-Base.3ds");
	}
	else if (type == FIRE) {
		obstacleModel = new Model_3DS(position.x, position.y, position.z,
			0.004, 0.002, 0.004,
			rotation.x, rotation.y, rotation.z);
		obstacleModel->Load("models/fire/fire.3ds");
		obstacleModel->Objects[0].pos.y = -20;
		obstacleModel->Objects[1].pos.y = 100000000000;
		obstacleModel->Objects[2].pos.y = 100000000000;
		obstacleModel->Objects[3].pos.y = 100000000000;
		obstacleModel->Objects[4].pos.y = 100000000000;
		obstacleModel->Objects[5].pos.y = 100000000000;
		obstacleModel->Objects[6].pos.y = 100000000000;
		obstacleModel->Objects[7].pos.y = 100000000000;
		obstacleModel->Objects[8].pos.y = 100000000000;
		obstacleModel->Objects[9].pos.y = 100000000000;
		obstacleModel->Objects[10].pos.y = 100000000000;
		obstacleModel->Objects[11].pos.y = 100000000000;
		obstacleModel->Objects[12].pos.y = 100000000000;
		shiftFire();
	}
}

void Obstacle::shiftFire() {
	float shiftAmount = 10;
	switch (player->curDirection) {
	case POSITIVE_X:
		obstacleModel->Objects[0].pos.x -= shiftAmount;
		obstacleModel->Objects[0].pos.z += shiftAmount;
		break;
	case NEGATIVE_X:
		obstacleModel->Objects[0].pos.x -= shiftAmount;
		obstacleModel->Objects[0].pos.z += shiftAmount;
		break;
	case POSITIVE_Z:
		obstacleModel->Objects[0].pos.x += shiftAmount;
		obstacleModel->Objects[0].pos.z += shiftAmount;
		break;
	case NEGATIVE_Z:
		obstacleModel->Objects[0].pos.x -= shiftAmount + 5;
		obstacleModel->Objects[0].pos.z += shiftAmount;
		break;
	}
}

void Obstacle::draw() {
	obstacleModel->Draw();
}
