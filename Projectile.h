#pragma once
#include "Engine\Graphics\Sprite.h" 
#include <string>
#include <math.h>
#include "Camera.h"
#include "Engine\Engine.h"

class Projectile {
public:
	Projectile();
	Projectile(float xStart, float yStart, float xDir, float yDir, float speed, std::string spritePath, float width, float height);
	float getXPos();
	float getYPos();
	bool exists;
	void Update();
	void Render();
	float getWidth();
	float getHeight();

private:
	Sprite projectileSprite;
	float xPos;
	float yPos;
	float initialXPos;
	float initialYPos;
	float xVel;
	float yVel;
	float width;
	float height;


};