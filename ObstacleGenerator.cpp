#include "ObstacleGenerator.h"

#include <vector>
#include <iostream>

ObstacleGenerator::ObstacleGenerator(std::vector<GroundInfo>* grounds, Gamemode mode, Player* pl) {
	groundArray = grounds;
	currentMode = mode;
	player = pl;
	obstacles = std::vector<Obstacle*>();
}

void ObstacleGenerator::generateObstacles() {
	for (int i = 1; i < groundArray->size(); i++) {
		auto ground = groundArray->at(i);

		double x = -1, z = 0, y = 0.015, rot = 0;

		double randomVerticalOffset = util::randomNumber(400, 900) / 1000.0;

		double horizOffsets[] = { -0.06, 0, 0.06 };
		double randomHorizontalOffset = horizOffsets[util::randomNumber(0, 2)];

		bool isFullObstacle = util::randomNumber(0, 100) <= 25;
		std::vector<std::pair<double, double>> toBeAdded;

		switch (ground.dir)
		{
		case NEGATIVE_X:
			x = ground.endPos + randomVerticalOffset;
			z = ground.centerPos;
			if (!isFullObstacle)
				toBeAdded.push_back({ x, z + randomHorizontalOffset });
			else {
				toBeAdded.push_back({ x, z + horizOffsets[0] });
				toBeAdded.push_back({ x, z + horizOffsets[1] });
				toBeAdded.push_back({ x, z + horizOffsets[2] });
			}
			break;
		case POSITIVE_X:
			x = ground.endPos - randomVerticalOffset;
			z = ground.centerPos;
			if (!isFullObstacle)
				toBeAdded.push_back({ x, z + randomHorizontalOffset });
			else {
				toBeAdded.push_back({ x, z + horizOffsets[0] });
				toBeAdded.push_back({ x, z + horizOffsets[1] });
				toBeAdded.push_back({ x, z + horizOffsets[2] });
			}
			break;
		case NEGATIVE_Z:
			z = ground.endPos + randomVerticalOffset;
			x = ground.centerPos;
			rot = 90;
			if (!isFullObstacle)
				toBeAdded.push_back({ x + randomHorizontalOffset, z });
			else {
				toBeAdded.push_back({ x + horizOffsets[0], z });
				toBeAdded.push_back({ x + horizOffsets[1], z });
				toBeAdded.push_back({ x + horizOffsets[2], z });
			}
			break;
		case POSITIVE_Z:
			z = ground.endPos - randomVerticalOffset;
			x = ground.centerPos;
			rot = 90;
			if (!isFullObstacle)
				toBeAdded.push_back({ x + randomHorizontalOffset, z });
			else {
				toBeAdded.push_back({ x + horizOffsets[0], z });
				toBeAdded.push_back({ x + horizOffsets[1], z });
				toBeAdded.push_back({ x + horizOffsets[2], z });
			}
			break;
		}

		for (auto& obs : toBeAdded)
			obstacles.push_back(new Obstacle(Vector(obs.first, y, obs.second), Vector(0, rot, 0), currentMode, player));
	}
}

void ObstacleGenerator::drawObstacles() {
	for (auto obs : obstacles) {
		obs->draw();
	}
}

extern GameStatus gameStatus;
extern int gameTime;
extern Player* player;
void ObstacleGenerator::tick() {
	for (auto& obs : obstacles) {		
		if (util::getDist(obs->position, Vector(player->curX, player->curY, player->curZ)) <= 0.05) {
			if (abs(obs->position.y - player->curY - player->curHeight) <= 0.0055) {
				if (gameStatus == PLAYING) {
					if(!player->gotShield) {
						if (currentMode == ROCK) {
							util::playSound("sounds/rock.wav");
						}
						else if (currentMode == FIRE) {
							util::playSound("sounds/fire.wav");
						}
						glutHideWindow();
						std::cout << "\x1B[2J\x1B[H";
						gameStatus = LOST;

						if (currentMode == ROCK) {
							util::showMessageBox("You collected " + std::to_string(player->coins) + " coins!");
						}
						else {
							util::showMessageBox("You scored " + std::to_string(gameTime) + "!");
						}
					}
				}
			}
		}
	}
}
