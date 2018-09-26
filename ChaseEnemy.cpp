#include "ChaseEnemy.h"

ChaseEnemy::ChaseEnemy() {
	currentXPos = 0;
	currentYPos = 0;
	initialXPos = 0;
	initialYPos = 0;
	xVel = 0;
	yVel = 0;
	health = 300;
	attackDamage = 1;
	chaseEnemySprite = Sprite("Assets/Art/Robot_Enemy_Cropped.png", initialXPos, initialYPos);
	chaseEnemySprite.SetScaleTo(1);
	exists = false;
}
//Gives ChaseEnemy object the player's projectile array.
void ChaseEnemy::setProjectileArray(std::array<Projectile, 5> projectileArray) {
	this->projectileArray = projectileArray;
}

//constructor used throughout program, gives a starting x position, y position, the block  array for the level, and player's projectile array
ChaseEnemy::ChaseEnemy(float _xPos, float _yPos, std::array<Block, 100> blockArray, std::array<Projectile, 5> projectileArray) {
	currentXPos = _xPos;
	currentYPos = _yPos;
	initialXPos = _xPos;
	initialYPos = _yPos;
	xVel = 0;
	yVel = 0;
	health = 300;
	attackDamage = 1;
	chaseEnemySprite = Sprite("Assets/Art/Robot_Enemy_Cropped.png", initialXPos, initialYPos);
	chaseEnemySprite.SetScaleTo(1);
	this->blockArray = blockArray;
	this->projectileArray = projectileArray;
	exists = true;
}

void ChaseEnemy::Update(float playerXPos) {
	if (std::abs(currentXPos - playerXPos) < 300) {
		ChasePlayer(playerXPos);
	}
	Jump();
	chaseEnemySprite.SetPosTo(currentXPos, currentYPos);
	currentXPos += xVel;
	currentYPos += yVel;
	checkCollisions();
	checkDeath();
}

void ChaseEnemy::checkDeath() {
	if (health <= 0) {
		exists = false;
	}
}

void ChaseEnemy::Render() {
	chaseEnemySprite.Render();
}

void ChaseEnemy::checkCollisions() {
	if (currentYPos < 1) {
		yVel = 0;
		hasJump = true;
	}
	else {		//Makes the enemy fall down when he isn't on the ground (gives the game a kind of gravity).

		if (yVel <= -1.5) {		//This assures that the enemy doesn't continuously accelerates forever.
			yVel = -1.5;	//This is its terminal velocity when falling. It doesn't fall faster than this.
		}
		else {
			yVel -= .003;		//This determines how fast the acceleration changes.
		}
	}
	//checks collisions of blocks with enemy
	//checks if any part of enemy sprite is inside any part of the blocks sprite
	for (int i = 0; i < blockArray.size(); i++) {	

		if (currentYPos + chaseEnemySprite.GetHeight() > blockArray[i].getYPos() && currentYPos < blockArray[i].getYPos() + 64) {
			if (currentXPos > blockArray[i].getXPos() + 32) {
				if ((currentYPos + chaseEnemySprite.GetHeight()) >(blockArray[i].getYPos())) {
					if ((currentXPos + xVel) <= (blockArray[i].getXPos() + 64)) {
						xVel = 0;
						currentXPos = (blockArray[i].getXPos() + 64);
					}
				}
			}
			else {
				if (currentYPos < blockArray[i].getYPos() + 64) {
					if ((currentXPos + xVel + chaseEnemySprite.GetWidth()) >(blockArray[i].getXPos())) {
						xVel = 0;
						currentXPos = (blockArray[i].getXPos()) - chaseEnemySprite.GetWidth();
					}
				}
			}
		}

		if (currentXPos + chaseEnemySprite.GetWidth() > blockArray[i].getXPos() && currentXPos < blockArray[i].getXPos() + 64) {
			if (currentYPos > blockArray[i].getYPos() + 32) {
				if ((currentXPos + chaseEnemySprite.GetWidth()) > (blockArray[i].getXPos())) {
					if ((currentYPos + yVel) <= (blockArray[i].getYPos() + 64)) {
						yVel = 0;
						hasJump = true;
						currentYPos = (blockArray[i].getYPos() + 64);
					}
				}
			}
			else {
				if (currentXPos < blockArray[i].getXPos() + 64) {
					if ((currentYPos + yVel + chaseEnemySprite.GetHeight()) >(blockArray[i].getYPos())) {
						yVel = 0;
						currentYPos = (blockArray[i].getYPos()) - chaseEnemySprite.GetHeight();
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
			if (currentYPos + chaseEnemySprite.GetHeight() > projectileArray[i].getYPos() && currentYPos < projectileArray[i].getYPos() + projectileArray[i].getHeight()) {
				if (currentXPos > projectileArray[i].getXPos() + projectileArray[i].getWidth() / 2) {
					if ((currentYPos + chaseEnemySprite.GetHeight()) > (projectileArray[i].getYPos())) {
						if ((currentXPos + xVel) <= (projectileArray[i].getXPos() + projectileArray[i].getWidth())) {
							projectileArray[i].exists = false;
							setHealth(getHealth() - 1);
							//cout << "hit" << endl;
						}
					}
				}
				else {
					if (currentYPos < projectileArray[i].getYPos() + projectileArray[i].getHeight()) {
						if ((currentXPos + xVel + chaseEnemySprite.GetWidth()) >(projectileArray[i].getXPos())) {
							projectileArray[i].exists = false;
							setHealth(getHealth() - 1);
							//cout << "hit" << endl;
						}
					}
				}
			}

			if (currentXPos + chaseEnemySprite.GetWidth() > projectileArray[i].getXPos() && currentXPos < projectileArray[i].getXPos() + projectileArray[i].getWidth()) {
				if (currentYPos > projectileArray[i].getYPos() + projectileArray[i].getWidth() / 2) {
					if ((currentXPos + chaseEnemySprite.GetWidth()) > (projectileArray[i].getXPos())) {
						if ((currentYPos + yVel) <= (projectileArray[i].getYPos() + projectileArray[i].getHeight())) {
							projectileArray[i].exists = false;
							setHealth(getHealth() - 1);
							//cout << "hit" << endl;
						}
					}
				}
				else {
					if (currentXPos < projectileArray[i].getXPos() + projectileArray[i].getWidth()) {
						if ((currentYPos + yVel + chaseEnemySprite.GetHeight()) >(projectileArray[i].getYPos())) {
							projectileArray[i].exists = false;
							setHealth(getHealth() - 1);
							//cout << "hit" << endl;
						}
					}
				}
			}
		}
	}
}

void ChaseEnemy::Jump() {
	if (hasJump) {
		if (yVel != 0) {	//Makes sure that the enemy jumps just once.
			hasJump = false;
		}
		yVel = 0.7;
	}
}

//Chases player if he is within a certain distance from it.
void ChaseEnemy::ChasePlayer(float playerXPos) {
	if (playerXPos > currentXPos) {		//Checks where the player is in relation to the enemy.
		xVel = 0.4;		//Enemy moves right if the player is to the right of the enemy.
	}
	else {
		xVel = -0.4;	//Enemy moves left if the player is to the left of the enemy.
	}
}

void ChaseEnemy::setHealth(int _health) {
	health = _health;
}

int ChaseEnemy::getHealth() {
	return health;
}

int ChaseEnemy::getAttackDamage() {
	return attackDamage;
}

float ChaseEnemy::getXPos() {
	return currentXPos;
}

float ChaseEnemy::getYPos() {
	return currentYPos;
}

int ChaseEnemy::getHeight() {
	return chaseEnemySprite.GetHeight();
}

int ChaseEnemy::getWidth() {
	return chaseEnemySprite.GetWidth();
}