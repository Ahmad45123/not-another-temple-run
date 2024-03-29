#include "PlayerCamera.h"


PlayerCamera::PlayerCamera(Player* player) {
	this->player = player;
}

void PlayerCamera::draw() {
	double centerX = player->curX;
	double centerY = player->curY;
	double centerZ = player->curZ;

	switch (player->curDirection)
	{
	case NEGATIVE_X:
		centerX -= 0.2;
		break;
	case POSITIVE_X:
		centerX += 0.2;
		break;
	case NEGATIVE_Z:
		centerZ -= 0.2;
		break;
	case POSITIVE_Z:
		centerZ += 0.2;
		break;
	}

	gluLookAt(player->curX, player->curY + player->curHeight + 0.04, player->curZ,
		centerX, centerY, centerZ,
		0, 1, 0);
}
