#include "BasicEnemy.h"


BasicEnemy::BasicEnemy() {
	currentXPos = 0;
	currentYPos = 0;
	initialXPos = 0;
	initialYPos = 0;
	xVel = 0;
	yVel = 0;
	health = 200;
	attackDamage = 1;
	basicEnemySprite = Sprite("Assets/Art/robotguard.png", initialXPos, initialYPos);
	basicEnemySprite.SetScaleTo(1);
	exists = false;
}

//constructor used throughout program, gives a starting x position, y position, the block  array for the level, and player's projectile array
BasicEnemy::BasicEnemy(float _xPos, float _yPos, std::array<Block, 100> blockArray, std::array<Projectile, 5> projectileArray) {
	currentXPos = _xPos;
	currentYPos = _yPos;
	initialXPos = _xPos;
	initialYPos = _yPos;
	xVel = -.5;
	yVel = 0;
	health = 200;
	attackDamage = 1;
	basicEnemySprite = Sprite("Assets/Art/robotguard.png", initialXPos, initialYPos);
	basicEnemySprite.SetScaleTo(1);
	this->blockArray = blockArray;
	this->projectileArray = projectileArray;
	exists = true;
}

void BasicEnemy::Render() {
	basicEnemySprite.Render();
}

void BasicEnemy::Update() {
	basicEnemySprite.SetPosTo(currentXPos, currentYPos);
	currentXPos += xVel;
	currentYPos += yVel;
	checkCollisions();
	checkDeath();
}

//This takes in player's projectiles to check if it has been hit.
void BasicEnemy::setProjectileArray(std::array<Projectile, 5> projectileArray) {
	this->projectileArray = projectileArray;
}

void BasicEnemy::checkDeath() {
	if (health <= 0) {
		exists = false;
	}
}

void BasicEnemy::checkCollisions() {
	//adds small value to y velocity each frame, simulates real gravity
	//has terminal falling velocity of 1.5 pixels per frame
	if (currentYPos < 1) {
		yVel = 0;
	}
	else {		//Makes the enemy fall down when he isn't on the ground (gives the game a kind of gravity).

		if (yVel <= -1.5) {		//This assures that the enemy doesn't continuously accelerates forever.
			yVel = -1.5;	//This is its terminal velocity when falling. It doesn't fall faster than this.
		}
		else {
			yVel -= .003;	//This determines how fast the acceleration changes.
		}
	}
	//checks collisions of blocks with enemy
	//checks if any part of enemy sprite is inside any part of the blocks sprite
	for (int i = 0; i < blockArray.size(); i++) {

		if (currentYPos + basicEnemySprite.GetHeight() > blockArray[i].getYPos() && currentYPos < blockArray[i].getYPos() + 64) {
			if (currentXPos > blockArray[i].getXPos() + 32) {
				if ((currentYPos + basicEnemySprite.GetHeight()) >(blockArray[i].getYPos())) {
					if ((currentXPos + xVel) <= (blockArray[i].getXPos() + 64)) {
						xVel = -xVel;
						currentXPos = (blockArray[i].getXPos() + 64);
					}
				}
			}
			else {
				if (currentYPos < blockArray[i].getYPos() + 64) {
					if ((currentXPos + xVel + basicEnemySprite.GetWidth()) >(blockArray[i].getXPos())) {
						xVel = -xVel;
						currentXPos = (blockArray[i].getXPos()) - basicEnemySprite.GetWidth();
					}
				}
			}
		}

		if (currentXPos + basicEnemySprite.GetWidth() > blockArray[i].getXPos() && currentXPos < blockArray[i].getXPos() + 64) {
			if (currentYPos > blockArray[i].getYPos() + 32) {
				if ((currentXPos + basicEnemySprite.GetWidth()) > (blockArray[i].getXPos())) {
					if ((currentYPos + yVel) <= (blockArray[i].getYPos() + 64)) {
						yVel = 0;
						currentYPos = (blockArray[i].getYPos() + 64);
					}
				}
			}
			else {
				if (currentXPos < blockArray[i].getXPos() + 64) {
					if ((currentYPos + yVel + basicEnemySprite.GetHeight()) >(blockArray[i].getYPos())) {
						yVel = 0;
						currentYPos = (blockArray[i].getYPos()) - basicEnemySprite.GetHeight();
					}
				}
			}
		}



		if (!blockArray[i].exists) {
			break;
		}
	}
	//For loop checks if any part of the projectile hits the enemy sprite.
	//If it does, then the enemy takes damage.
	for (int i = 0; i < projectileArray.size(); i++) {

		if (projectileArray[i].exists) {
			if (currentYPos + basicEnemySprite.GetHeight() > projectileArray[i].getYPos() && currentYPos < projectileArray[i].getYPos() + projectileArray[i].getHeight()) {
				if (currentXPos > projectileArray[i].getXPos() + projectileArray[i].getWidth() / 2) {
					if ((currentYPos + basicEnemySprite.GetHeight()) > (projectileArray[i].getYPos())) {
						if ((currentXPos + xVel) <= (projectileArray[i].getXPos() + projectileArray[i].getWidth())) {
							projectileArray[i].exists = false;
							setHealth(getHealth() - 50);
							//cout << "hit" << endl;
						}
					}
				}
				else {
					if (currentYPos < projectileArray[i].getYPos() + projectileArray[i].getHeight()) {
						if ((currentXPos + xVel + basicEnemySprite.GetWidth()) > (projectileArray[i].getXPos())) {
							projectileArray[i].exists = false;
							setHealth(getHealth() - 50);
							//cout << "hit" << endl;
						}
					}
				}
			}

			if (currentXPos + basicEnemySprite.GetWidth() > projectileArray[i].getXPos() && currentXPos < projectileArray[i].getXPos() + projectileArray[i].getWidth()) {
				if (currentYPos > projectileArray[i].getYPos() + projectileArray[i].getWidth() / 2) {
					if ((currentXPos + basicEnemySprite.GetWidth()) > (projectileArray[i].getXPos())) {
						if ((currentYPos + yVel) <= (projectileArray[i].getYPos() + projectileArray[i].getHeight())) {
							projectileArray[i].exists = false;
							setHealth(getHealth() - 50);
							//cout << "hit" << endl;
						}
					}
				}
				else {
					if (currentXPos < projectileArray[i].getXPos() + projectileArray[i].getWidth()) {
						if ((currentYPos + yVel + basicEnemySprite.GetHeight()) > (projectileArray[i].getYPos())) {
							projectileArray[i].exists = false;
							setHealth(getHealth() - 50);
							//cout << "hit" << endl;
						}
					}
				}
			}
		}
	}
}

void BasicEnemy::setHealth(int _health) {
	health = _health;
}

int BasicEnemy::getHealth() {
	return health;
}

int BasicEnemy::getAttackDamage() {
	return attackDamage;
}

float BasicEnemy::getXPos() {
	return currentXPos;
}

float BasicEnemy::getYPos() {
	return currentYPos;
}

int BasicEnemy::getHeight() {
	return basicEnemySprite.GetHeight();
}

int BasicEnemy::getWidth() {
	return basicEnemySprite.GetWidth();
}
