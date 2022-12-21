#pragma once

#include <vector>
#include <iostream>
#include "util.h"
#include "Obstacle.h"
#include <Player.h>

class ObstacleGenerator
{
public:

	std::vector<GroundInfo>* groundArray;
	std::vector<Obstacle*> obstacles;
	Gamemode currentMode;
	Player* player;

	ObstacleGenerator(std::vector<GroundInfo>* grounds, Gamemode mode, Player* pl);

	void generateObstacles();
	void drawObstacles();
	void tick();
};

