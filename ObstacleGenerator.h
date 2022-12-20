#pragma once

#include <vector>
#include "util.h"
#include "Obstacle.h"

class ObstacleGenerator
{
public:

	std::vector<GroundInfo>* groundArray;
	std::vector<Obstacle*> obstacles;
	Gamemode currentMode;

	ObstacleGenerator(std::vector<GroundInfo>* grounds, Gamemode mode) {
		groundArray = grounds;
		currentMode = mode;
		obstacles = std::vector<Obstacle*>();
	}

	void generateObstacles() {
		for (int i = 0; i < groundArray->size(); i++) {
			auto ground = groundArray->at(i);
			double x = -1, z = 0, y = 0.015;
			switch (ground.dir)
			{
			case NEGATIVE_X:
				x = ground.endPos + util::randomNumber(400, 900)/1000.0;
				z = ground.centerPos;
			default:
				break;
			}
			if(x != -1)
			obstacles.push_back(new Obstacle(Vector(x, y, z), Vector(0, 0, 0), currentMode));
		}
	}

	void drawObstacles() {
		for (auto obs : obstacles) {
			obs->draw();
		}
	}
};

