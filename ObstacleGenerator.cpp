#include "ObstacleGenerator.h"

ObstacleGenerator::ObstacleGenerator(std::vector<GroundInfo>* grounds, Gamemode mode) {
	groundArray = grounds;
	currentMode = mode;
	obstacles = std::vector<Obstacle*>();
}

void ObstacleGenerator::generateObstacles() {
	for (int i = 0; i < groundArray->size(); i++) {
		auto ground = groundArray->at(i);

		double x = -1, z = 0, y = 0.015, rot = 0;

		double randomVerticalOffset = util::randomNumber(400, 900) / 1000.0;

		double horizOffsets[] = { -0.06, 0, 0.06 };
		double randomHorizontalOffset = horizOffsets[util::randomNumber(0, 2)];

		switch (ground.dir)
		{
		case NEGATIVE_X:
			x = ground.endPos + randomVerticalOffset;
			z = ground.centerPos + randomHorizontalOffset;
			break;
		case POSITIVE_X:
			x = ground.endPos - randomVerticalOffset;
			z = ground.centerPos + randomHorizontalOffset;
			break;
		case NEGATIVE_Z:
			z = ground.endPos + randomVerticalOffset;
			x = ground.centerPos + randomHorizontalOffset;
			rot = 90;
			break;
		case POSITIVE_Z:
			z = ground.endPos - randomVerticalOffset;
			x = ground.centerPos + randomHorizontalOffset;
			rot = 90;
			break;
		}

		obstacles.push_back(new Obstacle(Vector(x, y, z), Vector(0, rot, 0), currentMode));
	}
}

void ObstacleGenerator::drawObstacles() {
	for (auto obs : obstacles) {
		obs->draw();
	}
}
