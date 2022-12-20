#include "Obstacle.h"

#include <iostream>
using namespace std;

Obstacle::Obstacle(Vector pos, Vector rot, Gamemode type) {
	position = pos;
	rotation = rot;
	obstacleModel = new Model_3DS(position.x, position.y, position.z, 0.002);
	obstacleModel->rot.x = rotation.x;
	obstacleModel->rot.y = rotation.y;
	obstacleModel->rot.z = rotation.z;
	if(type == ROCK)
		obstacleModel->Load("models/rocks/Rock07-Base.3ds");
}

void Obstacle::draw() {
	glPushMatrix();
	obstacleModel->Draw();
	glPopMatrix();
}
