#ifndef GAME_BIGBOSS
#define GAME_BIGBOSS

#include <cmath>
#include "Engine\Graphics\Sprite.h"
#include "Engine\Engine.h"
#include "Block.h"
#include "Projectile.h"
#include <array>
#include "GameState.h"


class BigBoss {
public:
	void Update(float playerXPos, float playerYPos);
	void Render();

	BigBoss();
	BigBoss(float _xPos, float _yPos, std::array<Block, 100> blockArray);

	float getXPos();
	float getYPos();
	int getAttackDamage();
	int getHealth();
	void setHealth(int _health);
	bool exists;
	std::array<Projectile, 5> playerProjectileArray;
	void setPlayerProjectileArray(std::array<Projectile, 5> playerProjectileArray);
	void checkDeath();
	int getHeight();
	int getWidth();
	std::array<Projectile, 1> projectileArray;

private:
	Sprite bossSprite;
	Sprite bossSpriteFlip;
	std::array<Block, 100> blockArray;
	
	float currentXPos;
	float currentYPos;
	float initialXPos;
	float initialYPos;
	float xVel;
	float yVel;
	int health;
	//Turns Projectile On/off
	bool projSwitch;
	//Switch for run attack set up
	bool runAttackSet;
	//Switch turns off jumping
	bool jumpSwitch;
	bool hasJump;
	void Jump();
	//Boss will dash across the stage back and forth
	void runAttack();
	//Boss will spawn at x,y position (based on health) and shoot projectiles
	void turretMode();
	//Switch sets up turret mode
	bool turretSet;
	int attackDamage;
	void checkCollisions();
	void attack(float playerXPos, float playerYPos);

};

#endif
