#include "GroundBuilder.h"

#include <glut.h>
#include <vector>

#include "util.h"

void GroundBuilder::drawBase() {
	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR);
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, grndTexture.texture[0]);	// Bind the ground texture

	glScaled(0.2, 0.02, 1.5);
	util::drawCube(1, 10);

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
	glPopMatrix();
}

GroundBuilder::GroundBuilder() {
	grndTexture.Load("Textures/ground.bmp");
}

void GroundBuilder::reset() {
	offsetZ = 0;
	offsetX = 0;
	curDir = Direction::NEGATIVE_Z;
}

void GroundBuilder::drawForward() {
	auto curX = offsetX;
	auto curZ = offsetZ;
	auto curAngle = 0;

	double groundsOffset = offsetZ;
	double midPoint = offsetZ;

	switch (curDir) {
	case NEGATIVE_Z:
		curZ -= 0.55;
		offsetZ = curZ - 0.75;
		curAngle = 0;
		groundsOffset = offsetZ;
		midPoint = curX;
		break;
	case POSITIVE_X:
		curX += 0.55;
		offsetX = curX + 0.75;
		curAngle = 90;
		groundsOffset = offsetX;
		midPoint = curZ;
		break;
	case POSITIVE_Z:
		curZ += 0.55;
		offsetZ = curZ + 0.75;
		curAngle = 180;
		groundsOffset = offsetZ;
		midPoint = curX;
		break;
	case NEGATIVE_X:
		curX -= 0.55;
		offsetX = curX - 0.75;
		curAngle = 270;
		groundsOffset = offsetX;
		midPoint = curZ;
		break;
	}

	if (isFillGrounds)
		grounds.push_back({ curDir, groundsOffset, midPoint });

	glPushMatrix();
	glTranslated(curX, 0, curZ);
	glRotated(curAngle, 0, 1, 0);
	drawBase();
	glPopMatrix();
}

void GroundBuilder::drawRight() {
	auto curX = offsetX;
	auto curZ = offsetZ;
	auto curAngle = 0;

	double groundsOffset = offsetZ;
	double midPoint = offsetZ;

	switch (curDir) {
	case NEGATIVE_Z:
		curDir = POSITIVE_X;
		curZ += 0.1;
		curX += 0.65;
		offsetZ = curZ;
		offsetX = curX + 0.75;
		curAngle = 90;
		groundsOffset = offsetX;
		midPoint = offsetZ;
		break;
	case POSITIVE_X:
		curDir = POSITIVE_Z;
		curX -= 0.1;
		curZ += 0.65;
		offsetX = curX;
		offsetZ = curZ + 0.75;
		curAngle = 180;
		groundsOffset = offsetZ;
		midPoint = offsetX;
		break;
	case POSITIVE_Z:
		curDir = NEGATIVE_X;
		curZ -= 0.1;
		curX -= 0.65;
		offsetZ = curZ;
		offsetX = curX - 0.75;
		curAngle = 270;
		groundsOffset = offsetX;
		midPoint = offsetZ;
		break;
	case NEGATIVE_X:
		curDir = NEGATIVE_Z;
		curX += 0.1;
		curZ -= 0.65;
		offsetX = curX;
		offsetZ = curZ - 0.75;
		curAngle = 0;
		groundsOffset = offsetZ;
		midPoint = offsetX;
		break;
	}

	if (isFillGrounds)
		grounds.push_back({ curDir, groundsOffset, midPoint });

	glPushMatrix();
	glTranslated(curX, 0, curZ);
	glRotated(curAngle, 0, 1, 0);
	drawBase();
	glPopMatrix();
}

void GroundBuilder::drawLeft() {
	auto curX = offsetX;
	auto curZ = offsetZ;
	auto curAngle = 0;

	double groundsOffset = offsetZ;
	double midPoint = offsetX;

	switch (curDir) {
	case NEGATIVE_Z:
		curDir = NEGATIVE_X;
		curZ += 0.1;
		curX -= 0.65;
		offsetZ = curZ;
		offsetX = curX - 0.75;
		curAngle = 270;
		groundsOffset = offsetX;
		midPoint = offsetZ;
		break;
	case POSITIVE_X:
		curDir = NEGATIVE_Z;
		curX -= 0.1;
		curZ -= 0.65;
		offsetX = curX;
		offsetZ = curZ - 0.75;
		curAngle = 0;
		groundsOffset = offsetZ;
		midPoint = offsetX;
		break;
	case POSITIVE_Z:
		curDir = POSITIVE_X;
		curZ -= 0.1;
		curX += 0.65;
		offsetZ = curZ;
		offsetX = curX + 0.75;
		curAngle = 90;
		groundsOffset = offsetX;
		midPoint = offsetZ;
		break;
	case NEGATIVE_X:
		curDir = POSITIVE_Z;
		curX += 0.1;
		curZ += 0.65;
		offsetX = curX;
		offsetZ = curZ + 0.75;
		curAngle = 180;
		groundsOffset = offsetZ;
		midPoint = offsetX;
		break;
	}

	if (isFillGrounds)
		grounds.push_back({ curDir, groundsOffset, midPoint });

	glPushMatrix();
	glTranslated(curX, 0, curZ);
	glRotated(curAngle, 0, 1, 0);
	drawBase();
	glPopMatrix();
}