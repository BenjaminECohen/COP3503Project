#include "BigBoss.h"

BigBoss::BigBoss() {
	currentXPos = 0;
	currentYPos = 0;
	initialXPos = 0;
	initialYPos = 0;
	xVel = 0;
	yVel = 0;
	projSwitch = true;
	runAttackSet = true;
	jumpSwitch = true;
	turretSet = true;
	health = 15000;
	attackDamage = 1;
	bossSprite = Sprite("Assets/Art/BigBoss.png", initialXPos, initialYPos);
	bossSprite.SetScaleTo(1);
	bossSpriteFlip = Sprite("Assets/Art/BigBossFlip.png", initialXPos, initialYPos);
	bossSpriteFlip.SetScaleTo(1);
	this->blockArray = blockArray;
	exists = false;

}

BigBoss::BigBoss(float _xPos, float _yPos, std::array<Block, 100> blockArray) {
	currentXPos = _xPos;
	currentYPos = _yPos;
	initialXPos = _xPos;
	initialYPos = _yPos;
	xVel = 0;
	yVel = 0;
	projSwitch = true;
	runAttackSet = true;
	jumpSwitch = true;
	turretSet = true;
	health = 15000;
	attackDamage = 1;
	bossSprite = Sprite("Assets/Art/BigBoss.png", initialXPos, initialYPos);
	bossSprite.SetScaleTo(1);
	bossSpriteFlip = Sprite("Assets/Art/BigBossFlip.png", initialXPos, initialYPos);
	bossSpriteFlip.SetScaleTo(1);
	this->blockArray = blockArray;
	exists = true;
}

void BigBoss::Update(float playerXPos, float playerYPos) {
	//Set a path
	if (abs(playerXPos - currentXPos) < 700) {
		attack(playerXPos, playerYPos);
	}
	for (int i = 0; i < projectileArray.size(); i++) {
		if (projectileArray[i].exists) {
			projectileArray[i].Update();
		}
	}
	if (health > 12000 || (health > 6000 && health < 9000) || health < 3000) {
		turretMode();
	}
	else {
		runAttack();
	}
	Jump();
	bossSprite.SetPosTo(currentXPos, currentYPos);
	bossSpriteFlip.SetPosTo(currentXPos, currentYPos);
	currentXPos += xVel;
	currentYPos += yVel;
	checkCollisions();
	checkDeath();
}

void BigBoss::Render() {
	if (xVel <= 0)
	{
		bossSprite.Render();
	}
	else
	{
		bossSpriteFlip.Render();
	}
	
	for (int i = 0; i < projectileArray.size(); i++) {
		if (projectileArray[i].exists) {
			projectileArray[i].Render();
		}
	}
}

int BigBoss::getHeight() {
	return bossSprite.GetHeight();
}

int BigBoss::getWidth() {
	return bossSprite.GetWidth();
}

void BigBoss::checkDeath() {
	if (health < 1) {
		exists = false;
		GameState::changeStates = true;
	}
}

void BigBoss::checkCollisions() {
	//adds small value to y velocity each frame, simulates real gravity
	//has terminal falling velocity of 1.5 pixels per frame
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

		if (currentYPos + bossSprite.GetHeight() > blockArray[i].getYPos() && currentYPos < blockArray[i].getYPos() + 64) {
			if (currentXPos > blockArray[i].getXPos() + 32) {
				if ((currentYPos + bossSprite.GetHeight()) >(blockArray[i].getYPos())) {
					if ((currentXPos + xVel) <= (blockArray[i].getXPos() + 64)) {
						xVel = 0;
						currentXPos = (blockArray[i].getXPos() + 64);
					}
				}
			}
			else {
				if (currentYPos < blockArray[i].getYPos() + 64) {
					if ((currentXPos + xVel + bossSprite.GetWidth()) >(blockArray[i].getXPos())) {
						xVel = 0;
						currentXPos = (blockArray[i].getXPos()) - bossSprite.GetWidth();
					}
				}
			}
		}

		if (currentXPos + bossSprite.GetWidth() > blockArray[i].getXPos() && currentXPos < blockArray[i].getXPos() + 64) {
			if (currentYPos > blockArray[i].getYPos() + 32) {
				if ((currentXPos + bossSprite.GetWidth()) > (blockArray[i].getXPos())) {
					if ((currentYPos + yVel) <= (blockArray[i].getYPos() + 64)) {
						yVel = 0;
						hasJump = true;
						currentYPos = (blockArray[i].getYPos() + 64);
					}
				}
			}
			else {
				if (currentXPos < blockArray[i].getXPos() + 64) {
					if ((currentYPos + yVel + bossSprite.GetHeight()) >(blockArray[i].getYPos())) {
						yVel = 0;
						currentYPos = (blockArray[i].getYPos()) - bossSprite.GetHeight();
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
	for (int i = 0; i < playerProjectileArray.size(); i++) {

		if (playerProjectileArray[i].exists) {
			if (currentYPos + bossSprite.GetHeight() > playerProjectileArray[i].getYPos() && currentYPos < playerProjectileArray[i].getYPos() + playerProjectileArray[i].getHeight()) {
				if (currentXPos > playerProjectileArray[i].getXPos() + playerProjectileArray[i].getWidth() / 2) {
					if ((currentYPos + bossSprite.GetHeight()) > (playerProjectileArray[i].getYPos())) {
						if ((currentXPos + xVel) <= (playerProjectileArray[i].getXPos() + playerProjectileArray[i].getWidth())) {
							playerProjectileArray[i].exists = false;
							setHealth(getHealth() - 1);
							//cout << "hit" << endl;
						}
					}
				}
				else {
					if (currentYPos < playerProjectileArray[i].getYPos() + playerProjectileArray[i].getHeight()) {
						if ((currentXPos + xVel + bossSprite.GetWidth()) >(playerProjectileArray[i].getXPos())) {
							playerProjectileArray[i].exists = false;
							setHealth(getHealth() - 1);
							//cout << "hit" << endl;
						}
					}
				}
			}

			if (currentXPos + bossSprite.GetWidth() > playerProjectileArray[i].getXPos() && currentXPos < playerProjectileArray[i].getXPos() + playerProjectileArray[i].getWidth()) {
				if (currentYPos > playerProjectileArray[i].getYPos() + playerProjectileArray[i].getWidth() / 2) {
					if ((currentXPos + bossSprite.GetWidth()) > (playerProjectileArray[i].getXPos())) {
						if ((currentYPos + yVel) <= (playerProjectileArray[i].getYPos() + playerProjectileArray[i].getHeight())) {
							playerProjectileArray[i].exists = false;
							setHealth(getHealth() - 1);
							//cout << "hit" << endl;
						}
					}
				}
				else {
					if (currentXPos < playerProjectileArray[i].getXPos() + playerProjectileArray[i].getWidth()) {
						if ((currentYPos + yVel + bossSprite.GetHeight()) >(playerProjectileArray[i].getYPos())) {
							playerProjectileArray[i].exists = false;
							setHealth(getHealth() - 1);
							//cout << "hit" << endl;
						}
					}
				}
			}
		}
	}
}

void BigBoss::Jump() {
	if (hasJump && jumpSwitch) {
		if (yVel != 0) {
			hasJump = false;
		}
		yVel = 1.0;
	}
}

void BigBoss::attack(float playerXPos, float playerYPos) {
	for (int i = 0; i < projectileArray.size(); i++) {
		if (!projectileArray[i].exists && projSwitch) {
			projectileArray[i] = Projectile(currentXPos + bossSprite.GetWidth() / 2,
				currentYPos + bossSprite.GetHeight() / 2,
				playerXPos,
				playerYPos,
				.9,
				"Assets/Art/ZavalanBullet.png",
				30,
				30);
			runAttackSet = true;
			break;
		}
	}
}

void BigBoss::setPlayerProjectileArray(std::array<Projectile, 5> playerProjectileArray) {
	this->playerProjectileArray = playerProjectileArray;
}

void BigBoss::runAttack()
{
	if (runAttackSet)
	{
		jumpSwitch = false;
		projSwitch = false;
		currentXPos = 1920.0;
		currentYPos = 64.0;
		runAttackSet = false;
		turretSet = true;
		yVel = 0;
		
	
	}
	if (currentXPos <=  768.0)
	{
		xVel = .8;
		//currentXPos = 1920.0;
		//currentYPos = 64.0;
	}
	if (currentXPos >= 1920.0)
	{
		xVel = -.8;
	}
	

}

void BigBoss::turretMode()
{
	if (turretSet)
	{
		jumpSwitch = true;
		projSwitch = true;
		currentXPos = 1984;
		currentYPos = 256;
		turretSet = false;
		xVel = 0;
	}
	
}

void BigBoss::setHealth(int _health) {
	health = _health;
}

int BigBoss::getHealth() {
	return health;
}

int BigBoss::getAttackDamage() {
	return attackDamage;
}

float BigBoss::getXPos() {
	return currentXPos;
}

float BigBoss::getYPos() {
	return currentYPos;
}


