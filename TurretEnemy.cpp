#include "TurretEnemy.h"

TurretEnemy::TurretEnemy() {
	currentXPos = 0;
	currentYPos = 0;
	initialXPos = 0;
	initialYPos = 0;
	xVel = 0;
	yVel = 0;
	health = 400;
	attackDamage = 1;
	turretSprite = Sprite("Assets/Art/FaceMonster2.png", initialXPos, initialYPos);
	turretSprite.SetScaleTo(1);
	exists = false;
}

//constructor used throughout program, gives a starting x position, y position, the block  array for the level, and player's projectile array
TurretEnemy::TurretEnemy(float _xPos, float _yPos, std::array<Block, 100> blockArray, std::array<Projectile, 5> playerProjectileArray) {
	currentXPos = _xPos;
	currentYPos = _yPos;
	initialXPos = _xPos;
	initialYPos = _yPos;
	xVel = 0;
	yVel = 0;
	health = 400;
	attackDamage = 1;
	turretSprite = Sprite("Assets/Art/turret2L_Cropped.png", initialXPos, initialYPos);
	turretSprite.SetScaleTo(1);
	this->blockArray = blockArray;
	this->playerProjectileArray = playerProjectileArray;
	exists = true;
}

void TurretEnemy::Update(float playerXPos, float playerYPos) {
	//If statement check how far the player is from the turret. If the player is within
	//750 pixels from the turret, the turret will shoot at the player's position.
	if (abs(playerXPos - currentXPos) < 750) {
		shoot(playerXPos, playerYPos);
	}
	//For loop Updates any of the turret's projectile that exists.
	for (int i = 0; i < projectileArray.size(); i++) {
		if (projectileArray[i].exists) {
			projectileArray[i].Update();
		}
	}
	turretSprite.SetPosTo(currentXPos, currentYPos);
	currentYPos += yVel;
	checkCollisions();
	checkDeath();
}
//Gives the turret object the player's projectile array to check if it has been hit or not (used in the checkcollision() method).
void TurretEnemy::setPlayerProjectileArray(std::array<Projectile, 5> playerProjectileArray) {
	this->playerProjectileArray = playerProjectileArray;
}

void TurretEnemy::checkDeath() {
	if (health <= 0) {
		exists = false;
	}
}

void TurretEnemy::Render() {
	turretSprite.Render();
	//For loop renders any of the turret's projectile that exists.
	for (int i = 0; i < projectileArray.size(); i++) {
		if (projectileArray[i].exists) {
			projectileArray[i].Render();
		}
	}
}

void TurretEnemy::shoot(float playerXPos, float playerYPos) {
	for (int i = 0; i < projectileArray.size(); i++) {
		//creates a new projectile in the projectile array if there is a spot open for it (i.e. there is
		//a projectile that doesn't exist). This projectile travels in the direction of the player's position.
		if (!projectileArray[i].exists) {
			projectileArray[i] = Projectile(currentXPos + turretSprite.GetWidth() / 2,
				currentYPos + turretSprite.GetHeight() / 2,
				playerXPos,
				playerYPos,
				.5,
				"Assets/Art/TurretBullet.png", 30, 30);
			break;
		}
	}
}

void TurretEnemy::checkCollisions() {
	if (currentYPos < 1) {
		yVel = 0;
		hasJump = true;
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

		if (currentYPos + turretSprite.GetHeight() > blockArray[i].getYPos() && currentYPos < blockArray[i].getYPos() + 64) {
			if (currentXPos > blockArray[i].getXPos() + 32) {
				if ((currentYPos + turretSprite.GetHeight()) >(blockArray[i].getYPos())) {
					if ((currentXPos + xVel) <= (blockArray[i].getXPos() + 64)) {
						xVel = 0;
						currentXPos = (blockArray[i].getXPos() + 64);
					}
				}
			}
			else {
				if (currentYPos < blockArray[i].getYPos() + 64) {
					if ((currentXPos + xVel + turretSprite.GetWidth()) >(blockArray[i].getXPos())) {
						xVel = 0;
						currentXPos = (blockArray[i].getXPos()) - turretSprite.GetWidth();
					}
				}
			}
		}

		if (currentXPos + turretSprite.GetWidth() > blockArray[i].getXPos() && currentXPos < blockArray[i].getXPos() + 64) {
			if (currentYPos > blockArray[i].getYPos() + 32) {
				if ((currentXPos + turretSprite.GetWidth()) > (blockArray[i].getXPos())) {
					if ((currentYPos + yVel) <= (blockArray[i].getYPos() + 64)) {
						yVel = 0;
						hasJump = true;
						currentYPos = (blockArray[i].getYPos() + 64);
					}
				}
			}
			else {
				if (currentXPos < blockArray[i].getXPos() + 64) {
					if ((currentYPos + yVel + turretSprite.GetHeight()) >(blockArray[i].getYPos())) {
						yVel = 0;
						currentYPos = (blockArray[i].getYPos()) - turretSprite.GetHeight();
					}
				}
			}
		}

		//For loop checks if any part of the projectile hits the enemy sprite.
		//If it does, then the enemy takes damage.
		for (int i = 0; i < playerProjectileArray.size(); i++) {

			if (playerProjectileArray[i].exists) {
				if (currentYPos + turretSprite.GetHeight() > playerProjectileArray[i].getYPos() && currentYPos < playerProjectileArray[i].getYPos() + playerProjectileArray[i].getHeight()) {
					if (currentXPos > playerProjectileArray[i].getXPos() + playerProjectileArray[i].getWidth() / 2) {
						if ((currentYPos + turretSprite.GetHeight()) > (playerProjectileArray[i].getYPos())) {
							if ((currentXPos + xVel) <= (playerProjectileArray[i].getXPos() + playerProjectileArray[i].getWidth())) {
								playerProjectileArray[i].exists = false;
								setHealth(getHealth() - 1);
								//cout << "hit" << endl;
							}
						}
					}
					else {
						if (currentYPos < playerProjectileArray[i].getYPos() + playerProjectileArray[i].getHeight()) {
							if ((currentXPos + xVel + turretSprite.GetWidth()) >(playerProjectileArray[i].getXPos())) {
								playerProjectileArray[i].exists = false;
								setHealth(getHealth() - 1);
								//cout << "hit" << endl;
							}
						}
					}
				}

				if (currentXPos + turretSprite.GetWidth() > playerProjectileArray[i].getXPos() && currentXPos < playerProjectileArray[i].getXPos() + playerProjectileArray[i].getWidth()) {
					if (currentYPos > playerProjectileArray[i].getYPos() + playerProjectileArray[i].getWidth() / 2) {
						if ((currentXPos + turretSprite.GetWidth()) > (playerProjectileArray[i].getXPos())) {
							if ((currentYPos + yVel) <= (playerProjectileArray[i].getYPos() + playerProjectileArray[i].getHeight())) {
								playerProjectileArray[i].exists = false;
								setHealth(getHealth() - 1);
								//cout << "hit" << endl;
							}
						}
					}
					else {
						if (currentXPos < playerProjectileArray[i].getXPos() + playerProjectileArray[i].getWidth()) {
							if ((currentYPos + yVel + turretSprite.GetHeight()) >(playerProjectileArray[i].getYPos())) {
								playerProjectileArray[i].exists = false;
								setHealth(getHealth() - 1);
								//cout << "hit" << endl;
							}
						}
					}
				}
			}
		}

		if (!blockArray[i].exists) {
			break;
		}
	}
}

void TurretEnemy::setHealth(int _health) {
	health = _health;
}

int TurretEnemy::getHealth() {
	return health;
}

int TurretEnemy::getAttackDamage() {
	return attackDamage;
}

float TurretEnemy::getXPos() {
	return currentXPos;
}

float TurretEnemy::getYPos() {
	return currentYPos;
}

int TurretEnemy::getHeight() {
	return turretSprite.GetHeight();
}

int TurretEnemy::getWidth() {
	return turretSprite.GetWidth();
}

Projectile TurretEnemy::getProjectile(int i) {
	return projectileArray[i];
}