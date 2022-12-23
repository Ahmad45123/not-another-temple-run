#pragma once

#include <vector>
#include <iostream>
#include "util.h"
#include "Coin.h"
#include <Player.h>

class CoinsGenerator
{
public:

	std::vector<GroundInfo>* groundArray;
	std::vector<Coin*> coins;
	Gamemode currentMode;
	Player* player;

	CoinsGenerator(std::vector<GroundInfo>* grounds, Gamemode mode, Player* pl);

	void generateCoins();
	void drawCoins();
	void tick();
	void printCoins();
};

