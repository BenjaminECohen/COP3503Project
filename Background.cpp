#include "Background.h"

Background::Background(std::string backgroundSpritePath)
{
	xPos = 0;
	yPos = 0;
	backgroundSprite = Sprite(backgroundSpritePath, xPos, yPos);
	backgroundSprite.SetScaleTo(1);
}

Background::Background() {

}

void Background::Update()
{
	//Sets the background sprite to move slightly with the camera
	xPos = Camera::getXCoord()* (.33);
	backgroundSprite.SetPosTo(xPos, yPos);
	
}

void Background::Render()
{
	backgroundSprite.Render();
}