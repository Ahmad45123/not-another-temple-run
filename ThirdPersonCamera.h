#pragma once
#include <Player.h>
class ThirdPersonCamera
{
public:
	Player* player;

	ThirdPersonCamera(Player* player) {
		this->player = player;
	}

	void draw() {
		double centerX = player->curX;
		double centerY = player->curY;
		double centerZ = player->curZ;
		
		double eyeX = player->curX;
		double eyeY = player->curY + 0.1;
		double eyeZ = player->curZ;

		switch (player->curDirection)
		{
		case NEGATIVE_X:
			centerX -= 0.2;
			eyeX += 0.2;
			break;
		case POSITIVE_X:
			centerX += 0.2;
			eyeX -= 0.2;
			break;
		case NEGATIVE_Z:
			centerZ -= 0.2;
			eyeZ += 0.2;
			break;
		case POSITIVE_Z:
			centerZ += 0.2;
			eyeZ -= 0.2;
			break;
		}

		gluLookAt(eyeX, eyeY, eyeZ,
			centerX, centerY, centerZ,
			0, 1, 0);
	}

};

