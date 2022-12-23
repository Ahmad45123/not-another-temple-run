#pragma once

#include "Model_3DS.h"
#include "Vector.h"
#include <util.h>

class Shield
{
public:
	Vector position;
	Vector rotation;
	Model_3DS* shieldModel;
	bool taken;

	class Shield(Vector pos, Vector rot, Gamemode type);

	void draw(int rotAng);
};

