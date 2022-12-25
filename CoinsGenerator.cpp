#include "CoinsGenerator.h"

#include <vector>
#include <iostream>

CoinsGenerator::CoinsGenerator(std::vector<GroundInfo>* grounds, Gamemode mode, Player* pl) {
	groundArray = grounds;
	currentMode = mode;
	player = pl;
	coins = std::vector<Coin*>();
}

void CoinsGenerator::generateCoins() {
	for (int i = 1; i < groundArray->size(); i++) {
		auto ground = groundArray->at(i);

		double x = -1, z = 0, y = 0.015 +0.03, rot = 0;

		double randomVerticalOffset = util::randomNumber(100, 900) / 1000.0;

		double horizOffsets[] = { -0.06, 0, 0.06 };
		double randomHorizontalOffset = horizOffsets[util::randomNumber(0, 2)];

		//bool isFullObstacle = util::randomNumber(0, 100) <= 25;
		std::vector<std::pair<double, double>> toBeAdded;

		int numberOfCoinsPerGroup = util::randomNumber(0, 5);

		while (numberOfCoinsPerGroup > 0) {
			randomVerticalOffset += 0.1;
			switch (ground.dir)
			{
			case NEGATIVE_X:
				x = ground.endPos + randomVerticalOffset;
				z = ground.centerPos;
				//if(x + randomHorizontalOffset < 1.5)
					toBeAdded.push_back({ x, z + randomHorizontalOffset });

				break;
			case POSITIVE_X:
				x = ground.endPos - randomVerticalOffset;
				z = ground.centerPos;
				//if (x < ground.endPos)
					toBeAdded.push_back({ x, z + randomHorizontalOffset });

				break;
			case NEGATIVE_Z:
				z = ground.endPos + randomVerticalOffset;
				x = ground.centerPos;
				rot = 90;
				//if (z < ground.endPos)
					toBeAdded.push_back({ x + randomHorizontalOffset, z });

				break;
			case POSITIVE_Z:
				z = ground.endPos - randomVerticalOffset;
				x = ground.centerPos;
				rot = 90;
				//if (z < ground.endPos)
					toBeAdded.push_back({ x + randomHorizontalOffset, z });

				break;
			}

			numberOfCoinsPerGroup -= 1;
		}

		

		for (auto& obs : toBeAdded)
			coins.push_back(new Coin(Vector(obs.first, y, obs.second), Vector(0, rot, 0), currentMode));
	}
}

void CoinsGenerator::drawCoins() {
	for (auto obs : coins) {
		obs->draw(rotAng);
	}
}

void CoinsGenerator::tick() {
	rotAng += 1;
	for (auto& obs : coins) {
		if (util::getDist(obs->position, Vector(player->curX, player->curY, player->curZ)) <= 0.05) {
			if (abs(( obs->position.y - 0.03 ) - player->curY - player->curHeight) <= 0.0055) {
				if (player->STEP_SIZE != 0 && !obs->taken) { // TODO: change this
					util::playSound("sounds/coin.wav");
					// Inc the coins by one
					obs->taken = true;
					player->coins++;
				}
			}
		}
	}
}



void CoinsGenerator::printCoins() {
	
	//glPushMatrix();
	//glColor3f(1.0, 0.0, 0.0);
	//glRasterPos3f(0, 0, -20); //define position on the screen
	//const char* string = "Total Coins "+ player->coins;

	//while (*string) {
		//glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *string++);
	//}
	//glPopMatrix();

}