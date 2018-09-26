#ifndef GAME_BASICENEMY
#define GAME_BASICENEMY

#include "Engine\Graphics\Sprite.h"
#include "Engine\Engine.h"
#include "Block.h"
#include <array>
#include "Projectile.h"


class BasicEnemy {
public:
	void Update();
	void Render();

	BasicEnemy();
	BasicEnemy(float _xPos, float _yPos, std::array<Block, 100> blockArray, std::array<Projectile, 5> projectileArray);

	float getXPos();
	float getYPos();
	int getHeight();
	int getWidth(); 
	int getAttackDamage();
	void setHealth(int _health);
	int getHealth();
	bool exists;
	void checkDeath();
	void setProjectileArray(std::array<Projectile, 5> projectileArray);

private:
	Sprite basicEnemySprite;
	std::array<Block, 100> blockArray;
	std::array<Projectile, 5> projectileArray;
	float currentXPos;
	float currentYPos;
	float initialXPos;
	float initialYPos;
	float xVel;
	float yVel;
	int health;
	int attackDamage;
	void checkCollisions();
};

#endif
