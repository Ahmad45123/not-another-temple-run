#pragma once

#include "Model_3DS.h"
#include "Vector.h"
#include <util.h>

class Coin
{
public:
	Vector position;
	Vector rotation;
	Model_3DS* coinModel;
	bool taken;
	//int rotAng = 30;

	class Coin(Vector pos, Vector rot, Gamemode type);

	void timerFunc(int v);
	void draw(int rotAng);
};

