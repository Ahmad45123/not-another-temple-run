#include "ShieldGenerator.h"

#include <vector>
#include <iostream>

ShieldGenerator::ShieldGenerator(std::vector<GroundInfo>* grounds, Gamemode mode, Player* pl) {
	groundArray = grounds;
	currentMode = mode;
	player = pl;
	shields = std::vector<Shield*>();
}
bool groundGotAShieldAlready(int test_ground, std::vector<int> groundsContainingShield) {
	for (int i = 0; i < groundsContainingShield.size(); i++) {
		// test groudn got a shield and we neeed to find another one.
		if (groundsContainingShield.at(i) == test_ground) return true;
	}
	return false;
}
void ShieldGenerator::generateShield() {
	
		std::vector<int> groundsContainingShield;
		double rarity = 0.5;
		int numberOfGroundContainingShields = rarity * groundArray->size();

		for (int i = 0; i < numberOfGroundContainingShields; i++) {
			int randomGround = util::randomNumber(0, groundArray->size()-1);
			while (groundGotAShieldAlready(randomGround, groundsContainingShield)) {
				randomGround = util::randomNumber(0, groundArray->size() - 1);
			}
			groundsContainingShield.push_back(randomGround);
		}
		

		for(int i = 0; i < groundsContainingShield.size(); i++){
		
			int groundIndex = groundsContainingShield.at(i);
			auto ground = groundArray->at(groundIndex);

			double x = -1, z = 0, y = 0.015 + 0.03 , rot = 0;

			double randomVerticalOffset = util::randomNumber(100, 900) / 1000.0;

			double horizOffsets[] = { -0.06, 0, 0.06 };
			double randomHorizontalOffset = horizOffsets[util::randomNumber(0, 2)];

			//bool isFullObstacle = util::randomNumber(0, 100) <= 25;
			std::vector<std::pair<double, double>> toBeAdded;


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


			for (auto& obs : toBeAdded)
				shields.push_back(new Shield(Vector(obs.first, y, obs.second), Vector(0, rot, 0), currentMode));
		
		}

	
}

void ShieldGenerator::drawShield() {
	for (auto obs : shields) {
		obs->draw();
	}
}


void ShieldGenerator::handleShieldExpiry() {
	//gets called every 10 ms
	if (player->gotShield) {
		shieldRemainingTime -= 10 * 0.001;
		if (shieldRemainingTime <= 0) {
			player->gotShield = false;
			shieldRemainingTime = originalShieldTime;
		}
	}
}
void ShieldGenerator::tick() {

	handleShieldExpiry();

	for (auto& obs : shields) {
		if (util::getDist(obs->position, Vector(player->curX, player->curY, player->curZ)) <= 0.05) {
			if (abs((obs->position.y - 0.03) - player->curY - player->curHeight) <= 0.0055) {
				if (player->STEP_SIZE != 0) { // TODO: change this
					util::playSound("sounds/shield.wav");
					obs->taken = true;
					shieldRemainingTime = originalShieldTime;
					player->gotShield = true;
				}
			}
		}
	}
}



void ShieldGenerator::printCoins() {

	glPushMatrix();
	//glColor3f(1.0, 0.0, 0.0);
	glRasterPos3f(0, 0, -20); //define position on the screen
	const char* string = "Total Coins " + player->coins;

	while (*string) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *string++);
	}
	glPopMatrix();

}