#include "Shield.h"

#include <iostream>
using namespace std;

Shield::Shield(Vector pos, Vector rot, Gamemode type) {
	
	position = pos;
	rotation = rot;
	shieldModel = new Model_3DS(position.x, position.y, position.z,
		0.005, 0.0030, 0.0050,
		rotation.x, 40 , 90);
	taken = false;
	if (type == FIRE)
		shieldModel->Load("models/shield/shield_2.3ds");
}

void Shield::draw(int rotAng) {
	//may add the player to be here as well and check if he got a shield or no.
	if (!taken){
		shieldModel->rot.y = rotAng;
		shieldModel->Draw();
	}
		

}
