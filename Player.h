#pragma once
#include "Engine\Engine.h"
#include "Engine\Input\Keyboard.h"
#include "Engine\Input\Mouse.h"
#include "Engine\Graphics\Sprite.h"

class Player {
public:

	void Update();
	void Render();
	Player();
	Player(float xPos, float  yPos);

private:

	bool hasJump;
	int cameraCoordX;
	int cameraCoordY;
	void checkCollisions();
	void keyHandle();
	void slowDown();
	void moveCamera();
	float xPos;
	float yPos;
	float xVel;
	float yVel;
	float health;
	Sprite playerSprite;

};