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
	Direction curDir = NEGATIVE_Z;
	bool isFillGrounds = true;
	std::vector<GroundInfo> grounds;

	GroundBuilder();

	void drawBase();
	void reset();

	void drawForward();
	void drawRight();
	void drawLeft();
};

