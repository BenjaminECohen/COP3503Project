#pragma once
#include "Engine\Engine.h"
#include "Engine\Input\Keyboard.h"
#include "Engine\Input\Mouse.h"
#include "Engine\Graphics\Sprite.h"
#include "Map.h"
#include "Projectile.h"
#include "Camera.h"
#include "GameState.h"
#include "BasicEnemy.h"
#include "ChaseEnemy.h"
#include "TurretEnemy.h"
#include <windows.h>

class Player {
public:

	void Update();
	void Render();
	Player();
	Player(float xPos, float  yPos, std::array<Block, 100> blockArray, std::array<BasicEnemy, 5> basicEnemyArray);
	float getYPos();
	float getXPos();
	float getWidth();
	float getHeight();
	float getCameraCoordX();
	float getCameraCoordY();
	void setBasicEnemyArray(std::array<BasicEnemy, 5> basicEnemyArray);
	void setChaseEnemyArray(std::array<ChaseEnemy, 5> chaseEnemyArray);
	void setTurretEnemyArray(std::array<TurretEnemy, 5> turretEnemyArray);
	void setBoss(BigBoss bigBoss);
	void getHurt();
	bool vulnerable;
	int vulTime;
	std::array<Projectile, 5> projectileArray;
	

private:
	bool hasJump;
	void checkCollisions();
	void keyHandle();
	void slowDown();
	void moveCamera();
	void shoot();
	float xPos;
	float yPos;
	float xVel;
	float yVel;
	float health;
	Sprite playerSprite;
	Sprite playerSpriteFlip;
	Sprite heart1;
	Sprite heart2;
	Sprite heart3;
	std::array<Block, 100> blockArray;
	std::array<BasicEnemy, 5> basicEnemyArray;
	std::array<ChaseEnemy, 5> chaseEnemyArray;
	std::array<TurretEnemy, 5> turretEnemyArray;
	BigBoss bigBoss;
};


/*for (int i = 0; i < basicEnemyArray.size(); i++) {
		if (basicEnemyArray[i].exists) {
			if (yPos + playerSprite.GetHeight() > basicEnemyArray[i].getYPos() && yPos < basicEnemyArray[i].getYPos() + basicEnemyArray[i].getHeight()) {
				if (xPos > basicEnemyArray[i].getXPos() + basicEnemyArray[i].getWidth() / 2) {
					if ((yPos + playerSprite.GetHeight()) > (basicEnemyArray[i].getYPos())) {
						if ((xPos + xVel) <= (basicEnemyArray[i].getXPos() + basicEnemyArray[i].getWidth())) {
							//get hurt
							getHurt();

							break;
						}
					}
				}
				else {
					if (yPos < basicEnemyArray[i].getYPos() + basicEnemyArray[i].getHeight()) {
						if ((xPos + xVel + playerSprite.GetWidth()) > (basicEnemyArray[i].getXPos())) {
							//get hurt
							getHurt();

							break;
						}
					}
				}
			}
			else if (xPos + playerSprite.GetWidth() > basicEnemyArray[i].getXPos() && xPos < basicEnemyArray[i].getXPos() + basicEnemyArray[i].getWidth()) {
				if (yPos > basicEnemyArray[i].getYPos() + basicEnemyArray[i].getHeight() / 2) {
					if ((xPos + playerSprite.GetWidth()) > (basicEnemyArray[i].getXPos())) {
						if ((yPos + yVel) <= (basicEnemyArray[i].getYPos() + basicEnemyArray[i].getHeight())) {
							//get hurt
							getHurt();

							break;
						}
					}
				}
				else {
					if (xPos < basicEnemyArray[i].getXPos() + basicEnemyArray[i].getWidth()) {
						if ((yPos + yVel + playerSprite.GetHeight()) > (basicEnemyArray[i].getYPos())) {
							//get hurt
							getHurt();

							break;
						}
					}
				}
			}
		}
	}
	*/