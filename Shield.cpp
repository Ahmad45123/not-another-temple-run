#include "Shield.h"

#include <iostream>
using namespace std;

Shield::Shield(Vector pos, Vector rot, Gamemode type) {
	
	position = pos;
	rotation = rot;
	shieldModel = new Model_3DS(position.x, position.y, position.z,
		0.025, 0.015, 0.025,
		rotation.x, 40 , 90);
	taken = false;
	if (type == ROCK)
		shieldModel->Load("models/shield/shield.3ds");
}

void Shield::draw() {
	//may add the player to be here as well and check if he got a shield or no.
	if(!taken)
		shieldModel->Draw();

}
