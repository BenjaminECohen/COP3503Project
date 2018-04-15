#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include "Engine\Graphics\Sprite.h"

class Map {
public:
	Map(std::string mapFile);
	void Render();
	void Update();
	void LoadMap(std::string mapFile);

private:
	bool first;
	std::string mapString;
	std::ifstream input;
	std::array<std::string, 12> map;
	Sprite sprite;
	int count;
};