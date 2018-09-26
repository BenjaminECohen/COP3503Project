#ifndef GAME_CHASEENEMY
#define GAME_CHASEENEMY

#include <cmath>
#include "Engine\Graphics\Sprite.h"
#include "Engine\Engine.h"
#include "Block.h"
#include "Projectile.h"
#include <array>

class ChaseEnemy {

public:
	void Update(float playerXPos);
	void Render();

	ChaseEnemy();
	ChaseEnemy(float _xPos, float _yPos, std::array<Block, 100> blockArray, std::array<Projectile, 5> projectileArray);

	float getXPos();
	float getYPos();
	int getHeight();
	int getWidth();
	int getAttackDamage();
	int getHealth();
	void setHealth(int _health);
	bool exists;
	void setProjectileArray(std::array<Projectile, 5> projectileArray);
	void checkDeath();

private:
	Sprite chaseEnemySprite;
	std::array<Block, 100> blockArray;
	std::array<Projectile, 5> projectileArray;
	bool hasJump;
	float currentXPos;
	float currentYPos;
	float initialXPos;
	float initialYPos;
	float xVel;
	float yVel;
	int health;
	int attackDamage;
	void ChasePlayer(float playerXPos);
	void Patrol();
	void Jump();
	void checkCollisions();
};

#endif
