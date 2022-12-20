#pragma once

#include "Model_3DS.h"
#include "Vector.h"
#include <util.h>

class Obstacle
{
public:
	Vector position;
	Vector rotation;
	Model_3DS* obstacleModel;

	Obstacle(Vector pos, Vector rot, Gamemode type);

	void draw();
};

