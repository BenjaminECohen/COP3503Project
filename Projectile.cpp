#include "Projectile.h"

Projectile::Projectile() {
	xPos = 0;
	yPos = 0;
	xVel = 0;
	yVel = 0;
	exists = false;
}

//Spawns the projectile and launches it in the direction of the mouse (using its "x" and "y" components) via vector addition.
Projectile::Projectile(float xStart, float yStart, float xDir, float yDir, float speed, std::string spritePath, float width, float height) {
	xPos = xStart;
	yPos = yStart;
	initialXPos = xStart;
	initialYPos = yStart;
	xVel = ((1/(sqrt((xDir - xStart)*(xDir - xStart) + (yDir - yStart)*(yDir - yStart)))*(xDir-xStart))*speed);
	yVel = ((1/(sqrt((xDir - xStart)*(xDir - xStart) + (yDir - yStart)*(yDir - yStart)))*(yDir-yStart))*speed);
	projectileSprite = Sprite(spritePath, xStart, yStart);
	projectileSprite.SetScaleTo(1);
	exists = true;
	this->width = width;
	this->height = height;
}

float Projectile::getWidth() {
	return width;
}

float Projectile::getHeight() {
	return height;
}

float Projectile::getXPos() {
	return xPos;
}

float Projectile::getYPos() {
	return yPos;
}

void Projectile::Update() {
		xPos += xVel;
		yPos += yVel;
		projectileSprite.SetPosTo(xPos, yPos);
		//Projectile stops existing once its a certain distance away from its initial position.
		//Uses the distance formula to calulate its distance from initial position.
		if (sqrt(((xPos - initialXPos)*(xPos - initialXPos) + (yPos - initialYPos)*(yPos - initialYPos))) > 700) {
			xPos = 0;
			yPos = 0;
			xVel = 0;
			yVel = 0;
			exists = false;
		}
	
}

void Projectile::Render() {
	if (exists) {
		projectileSprite.Render(width, height);
	}
}

