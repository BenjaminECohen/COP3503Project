#include "Map.h"

Map::Map(std::string mapFile) {
	mapString = "";
}

Map::Map() {
	mapString = "";
}

//players array of projectiles, used for giving to all enemies, so they can check for collision
void Map::setProjectileArray(std::array<Projectile, 5> projectileArray) {
	this->projectileArray = projectileArray;
}

//set by player class, to be passed to enemies to check for collision,
//as well as to give coordinates to aim at for shooting enemies
void Map::setPlayerPos(float playerXPos, float playerYPos) {
	this->playerXPos = playerXPos;
	this->playerYPos = playerYPos;
}

//renders block array,  and all enemy arrays
void Map::Render() {

	for (int i = 0; i < blockArray.size(); i++) {
		if (blockArray[i].exists) {
			blockArray[i].Render();
		}
	}

	for (int i = 0; i < basicEnemyArray.size(); i++) {
		if (basicEnemyArray[i].exists) {
			basicEnemyArray[i].Render();
		}
	}

	for (int i = 0; i < chaseEnemyArray.size(); i++) {
		if (chaseEnemyArray[i].exists) {
			chaseEnemyArray[i].Render();
		}
	}
	for (int i = 0; i < turretEnemyArray.size(); i++) {
		if (turretEnemyArray[i].exists) {
			turretEnemyArray[i].Render();
		}
	}

	if (bigBoss.exists) {
		bigBoss.Render();
	}

}

//updates all enemies as well as passes them the updated player projectile array
void Map::Update(){
	for (int i = 0; i < basicEnemyArray.size(); i++) {
		if (basicEnemyArray[i].exists) {
			basicEnemyArray[i].Update();
			basicEnemyArray[i].setProjectileArray(projectileArray);
		}
	}

	for (int i = 0; i < chaseEnemyArray.size(); i++) {
		if (chaseEnemyArray[i].exists) {
			chaseEnemyArray[i].Update(playerXPos);
			chaseEnemyArray[i].setProjectileArray(projectileArray);
		}
	}

	for (int i = 0; i < turretEnemyArray.size(); i++) {
		if (turretEnemyArray[i].exists) {
			turretEnemyArray[i].Update(playerXPos, playerYPos);
			turretEnemyArray[i].setPlayerProjectileArray(projectileArray);
		}
	}

	if (bigBoss.exists){
		bigBoss.Update(playerXPos, playerYPos);
		bigBoss.setPlayerProjectileArray(projectileArray);
	}
}


//loads map from inputted text file
//text files are 12 lines of 64 integers 0-7
//0 - air
//1 - ground
//2 - spikes
//3 - teleporter to next level
//4 - basic enemies
//5 - chasing enemies
//6 - turret enemies
//7 - boss man
void Map::LoadMap(std::string mapFile) {

	std::ifstream input;
	std::string mapString;
	input.open(mapFile);
	std::array<std::string, 12> map;
	int count = 0;
	int basicEnemyCount = 0;

	while (!input.eof()) {
		input >> map[count];
		count++;
	}
	count = 0;
	basicEnemyCount = 0;
	chaseEnemyCount = 0;
	turretEnemyCount = 0;

	//clears block array from previous level
	for (int i = 0; i < blockArray.size(); i++) {
		blockArray[i] = Block();
	}
	//runs through text file, places blocks at coordinates based on place in text  file,
	//each integer representing a 64x64 pixel space
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 64; j++) {
			if (map[i].at(j) == '1') {
				if (GameState::getGameState() == 4) {
					blockArray[count] = Block(j * 64, ((11 - i) * 64), "Assets/Art/SpaceshipyGroundBlock.png", 1);
				} else {
					blockArray[count] = Block(j * 64, ((11 - i) * 64), "Assets/Art/Sand.png", 1);
				}
				count++;
				cout << "1";
			}
			else if (map[i].at(j) == '2') {
				blockArray[count] = Block(j * 64, ((11 - i) * 64), "Assets/Art/spikes.png", 2);
				count++;
				cout << "2";
			}
			else if (map[i].at(j) == '3') {
				blockArray[count] = Block(j * 64, ((11 - i) * 64), "Assets/Art/Teleporter.png", 3);
				count++;
				cout << "3";
			}
			else {
				cout << "0";
			}
		}
		cout << endl;
	}

	//runs through text file again checking for basic enemies, adding them to  basic enemy array,  giving them block array to check collisions
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 64; j++) {
			if (map[i].at(j) == '4') {
				basicEnemyArray[basicEnemyCount] = BasicEnemy(j * 64, ((11 - i) * 64), this->blockArray, this->projectileArray);
				basicEnemyCount++;
				cout << "4";
			}
			else {
				cout << "0";
			}
		}
		cout << endl;
	}
	//runs through text file again checking for chase enemies, adding them to  chase enemy array,  giving them block array to check collisions
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 64; j++) {
			if (map[i].at(j) == '5') {
				chaseEnemyArray[chaseEnemyCount] = ChaseEnemy(j * 64, ((11 - i) * 64), this->blockArray, this->projectileArray);
				chaseEnemyCount++;
				cout << "5";
			}
			else {
				cout << "0";
			}
		}
		cout << endl;
	}
	//runs through text file again checking for turret enemies, adding them to  turret enemy array,  giving them block array to check collisions
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 64; j++) {
			if (map[i].at(j) == '6') {
				turretEnemyArray[turretEnemyCount] = TurretEnemy(j * 64, ((11 - i) * 64), this->blockArray, this->projectileArray);
				turretEnemyCount++;
				cout << "6";
			}
			else {
				cout << "0";
			}
		}
		cout << endl;
	}
	//runs through text file again checking for boss enemies, adding them to the program, giving them block array to check collisions
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 64; j++) {
			if (map[i].at(j) == '7') {
				bigBoss = BigBoss(j * 64, ((11 - i) * 64), this->blockArray);
				cout << "7";
			}
			else {
				cout << "0";
			}
		}
		cout << endl;
	}
}
