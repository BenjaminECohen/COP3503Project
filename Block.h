#pragma once
#include "Engine\Graphics\Sprite.h"
class Block {
public:
	void Render();
	void Update();
	Block(int xPos, int yPos, std::string blockSprite, int blockType);
	Block();
	bool exists;
	int getXPos();
	int getYPos();
	int getBlockType();
private:
	int blockType;
	int xPos;
	int yPos;
	static int BLOCK_WIDTH;
	static int BLOCK_HEIGHT;
	Sprite blockSprite;
};