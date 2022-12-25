#pragma once
#include <Player.h>
#include "Camera.h"
class PlayerCamera : public Camera
{
public:
	Player* player;
	
	PlayerCamera(Player* player);
	virtual void draw();
};

