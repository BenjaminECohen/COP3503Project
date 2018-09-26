#pragma once

#include "GLFW\glfw3.h"
#include "Texture.h"

#include <iostream>
#include <string>
using namespace std;

/*
This Sprite class was copied from another programmer who made a video on Youtube on how to make a game.
We DID NOT take this class into consideration when counting the lines of code.\

This was programmed by Progrematic

Video: https://www.youtube.com/watch?v=4R5vSIZxr0M
*/

class Sprite {
public:
	Sprite();
	Sprite(string imagePath);
	Sprite(string imagePath, float _xPos, float _yPos);

	void Update();
	void Render();
	void Render(int width, int height);

	void SetRotTo(float x);
	void SetRotBy(float x);
	void SetPosTo(float x, float y);
	void SetPosBy(float x, float y);
	int GetWidth();
	int GetHeight();
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	void Jump();


	void SetScaleTo(float x);
	void SetScaleBy(float x);
	void SetScaleTo(float x, float y);


	void SetVelTo(float x);
	void SetVelBy(float x);
	void SetXVelTo(float x);
	void SetYVelTo(float y);
	void SetXYVelTo(float x, float y);
	void SetYVelBy(float y);
	void SetXVelBy(float x);
	void SetXYVelBy(float x, float y);

private:
	Texture texture;
	float xPos;
	float yPos;
	float rot;
	float xScale;
	float yScale;
	float xVel;
	float yVel;
	float width;
	float height;

};