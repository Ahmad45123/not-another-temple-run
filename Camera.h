#pragma once
class Camera
{
public:
	virtual void keyDown(int c) {};
	virtual void keyUp(int c) {};
	virtual void specialKeyDown(int c) {};
	virtual void specialKeyUp(int c) {};
	virtual void draw() {};
	virtual void tick() {};
};

