#ifndef GAME_BACKGROUND
#define GAME_BACKGROUND

#include "Engine\Graphics\Sprite.h"
#include "Camera.h"
#include <string>

class Background
{
public:
	void Update();
	void Render();
	float getXPos();
	float getYPos();

	Background(std::string backgroundSpritePath);
	Background();



private:
	Sprite backgroundSprite;
	float xPos;
	float yPos;

};


#endif

