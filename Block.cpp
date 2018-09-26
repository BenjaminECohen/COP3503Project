#include "Block.h"

int Block::BLOCK_HEIGHT = 64;
int Block::BLOCK_WIDTH = 64;


//block objects are what make up the map, they are size 64x64 pixels, 
//and all enemies and the player have collision with them
Block::Block(int xPos, int yPos, std::string blockSprite, int blockType) {
	this->xPos = xPos;
	this->yPos = yPos;
	Block::blockSprite = Sprite(blockSprite, xPos, yPos);
	this->blockSprite.SetScaleTo(1);
	exists = 1;
	this->blockType = blockType;
}


//block types:
//1 - ground
//2 - spikes
//3 - teleport to next level
int Block::getBlockType(){
	return blockType;
}

int Block::getXPos() {
	return xPos;
}

int Block::getYPos() {
	return yPos;
}

Block::Block() {
	xPos = -100;
	yPos = 0;

	exists = 0;
}

void Block::Render() {
	blockSprite.Render(BLOCK_WIDTH, BLOCK_HEIGHT);
}

void Block::Update() {

}