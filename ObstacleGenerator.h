#pragma once

#include <vector>
#include <iostream>
#include "util.h"
#include "Obstacle.h"

class ObstacleGenerator
{
public:

	std::vector<GroundInfo>* groundArray;
	std::vector<Obstacle*> obstacles;
	Gamemode currentMode;

	ObstacleGenerator(std::vector<GroundInfo>* grounds, Gamemode mode);

	void generateObstacles();
	void drawObstacles();
};

