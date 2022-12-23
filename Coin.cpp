#include "Coin.h"

#include <iostream>
using namespace std;

Coin::Coin(Vector pos, Vector rot, Gamemode type) {
	taken = false;
	position = pos;
	rotation = rot;

	coinModel = new Model_3DS(position.x, position.y, position.z,
		0.004, 0.02, 0.004,
		0, 30, 90);
	if (type == ROCK)
		coinModel->Load("models/coin/Coin.3ds");
}

void Coin::draw() {
	if(!taken)
		coinModel->Draw();

}
