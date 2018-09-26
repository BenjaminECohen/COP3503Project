#ifndef GAME_TURRETENEMY
#define GAME_TURRETENEMY

#include <cmath>
#include "Engine\Graphics\Sprite.h"
#include "Engine\Engine.h"
//#include "Player.h"
#include "Projectile.h"
#include "Block.h"
#include <array>

class TurretEnemy {
public:
	void Update(float playerXPos, float playerYPos);
	void Render();
	TurretEnemy();
	TurretEnemy(float _xPos, float _yPos, std::array<Block, 100> blockArray, std::array<Projectile, 5> playerProjectileArray);
	float getXPos();
	float getYPos();
	int getHeight();
	int getWidth();
	int getAttackDamage();
	int getHealth();
	void setHealth(int _health);
	Projectile getProjectile(int i);
	std::array<Projectile, 5> playerProjectileArray;
	std::array<Projectile, 1> projectileArray;
	void setPlayerProjectileArray(std::array<Projectile, 5> playerProjectileArray);
	void checkDeath();
	bool exists;

private:
	Sprite turretSprite;
	std::array<Block, 100> blockArray;
	bool hasJump;
	float currentXPos;
	float currentYPos;
	float initialXPos;
	float initialYPos;
	float xVel;
	float yVel;
	int health;
	int attackDamage;
	void checkCollisions();
	void shoot(float playerXPos, float playerYPos);
};

#endif
