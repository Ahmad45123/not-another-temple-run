#pragma once
#include "GLTexture.h"
#include <vector>

#include "util.h"

class GroundBuilder
{
public:
	GLTexture grndTexture;

	double offsetX = 0;
	double offsetZ = 0;
	double offsetY = -2.5;
	Direction curDir = NEGATIVE_Z;
	bool isFillGrounds = true;
	std::vector<GroundInfo> grounds;

	GroundBuilder(Gamemode type);

	void drawBase();
	void reset();

	void drawForward();
	void drawRight();
	void drawLeft();
};

