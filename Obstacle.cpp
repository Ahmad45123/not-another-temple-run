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
		for(int j = 1; j <= 12; j++)
			obstacleModel->Objects[j].pos.y = 100000000000;
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
