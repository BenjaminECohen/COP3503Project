#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include "Engine\Graphics\Sprite.h"
#include "Block.h"
#include "BasicEnemy.h"
#include "Projectile.h"
#include "ChaseEnemy.h"
#include "TurretEnemy.h"
#include "GameState.h"
#include "BigBoss.h"

class Map {
public:
	Map(std::string mapFile);
	Map();
	void Render();
	void Update();
	void LoadMap(std::string mapFile);
	std::array<Block, 100> blockArray;
	std::array<BasicEnemy, 5> basicEnemyArray;
	std::array<ChaseEnemy, 5> chaseEnemyArray;
	std::array<TurretEnemy, 5> turretEnemyArray;
	std::array<Projectile, 5> projectileArray;
	BigBoss bigBoss;
	void setProjectileArray(std::array<Projectile, 5> projectileArray);
	void setPlayerPos(float playerXPos, float playerYPos);
private:
	
	
	std::string mapString;
	std::ifstream input;
	std::array<std::string, 12> map;
	Sprite sprite;
	float playerXPos;
	float playerYPos;
	int count;
	int basicEnemyCount;
	int chaseEnemyCount;
	int turretEnemyCount;
};