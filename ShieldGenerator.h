#pragma once

#include <vector>
#include <iostream>
#include "util.h"
#include "Shield.h"
#include <Player.h>

class ShieldGenerator
{
public:

	std::vector<GroundInfo>* groundArray;
	std::vector<Shield*> shields;
	Gamemode currentMode;
	Player* player;
	double originalShieldTime = 5; // to reset the shield time after it ends or when a player takes a shield
	double shieldRemainingTime = originalShieldTime; //5 secs
	ShieldGenerator(std::vector<GroundInfo>* grounds, Gamemode mode, Player* pl);

	void generateShield();
	void drawShield();
	void tick();
	void printCoins();
	void handleShieldExpiry();
};

