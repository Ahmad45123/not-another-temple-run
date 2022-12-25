#include "Obstacle.h"

#include <iostream>
using namespace std;

Obstacle::Obstacle(Vector pos, Vector rot, Gamemode type) {
	position = pos;
	rotation = rot;
	obstacleModel = new Model_3DS(position.x, position.y, position.z, 
									0.001, 0.002, 0.001, 
								rotation.x, rotation.y, rotation.z);
	//if(type == ROCK)
	obstacleModel->Load("models/rocks/Rock07-Base.3ds");
}

void Obstacle::draw() {
	obstacleModel->Draw();
}
