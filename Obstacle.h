#pragma once

#include "Model_3DS.h"
#include "Vector.h"
#include <Player.h>
#include <util.h>

class Obstacle
{
public:
	Vector position;
	Vector rotation;
	Gamemode type;
	Player* player;
	Model_3DS* obstacleModel;

	Obstacle(Vector pos, Vector rot, Gamemode type, Player* pl);

	void shiftFire();
	void draw();
};

