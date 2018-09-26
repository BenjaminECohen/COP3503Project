#include "Sprite.h"

/*
This Sprite class was copied from another programmer who made a video on Youtube on how to make a game.
We DID NOT take this class into consideration when counting the lines of code.\

This was programmed by Progrematic

Video: https://www.youtube.com/watch?v=4R5vSIZxr0M
*/

Sprite::Sprite() {
	xPos = 0;
	yPos = 0;
	rot = 0;
	xVel = 1;
	yVel = 1;
	texture = Texture();
}

Sprite::Sprite(string imagePath) {
	texture = Texture(imagePath);
	xPos = 0;
	yPos = 0;
	rot = 0;
	xVel = 1;
	yVel = 1;
}

Sprite::Sprite(string imagePath, float _xPos, float _yPos) {
	texture = Texture(imagePath);
	xPos = _xPos;
	yPos = _yPos;
	rot = 0;
	xVel = 1;
	yVel = 1;
}

void Sprite::Update() {
	
}

void Sprite::SetPosTo(float x, float y) {
	xPos = x;
	yPos = y;
}

void Sprite::SetPosBy(float x, float y) {
	xPos += x;
	yPos += y;
}

void Sprite::SetRotTo(float x) {
	rot = x;
}

void Sprite::SetRotBy(float x) {
	rot += x;
}


void Sprite::SetScaleTo(float x) {
	xScale = x;
	yScale = x;
}

void Sprite::SetScaleBy(float x) {
	xScale += x;
	yScale += x;
}

void Sprite::SetScaleTo(float x, float y) {
	xScale = x;
	yScale = y;
}

void Sprite::SetVelTo(float x) {
	xVel = x;
	yVel = x;
}

void Sprite::SetXYVelTo(float x, float y) {
	xVel = x;
	yVel = y;
}

void Sprite::SetXVelTo(float x) {
	xVel = x;
}

void Sprite::SetYVelTo(float y) {
	yVel = y;
}

void Sprite::SetVelBy(float x) {
	xVel += x;
	yVel += x;
}

void Sprite::SetXVelBy(float x) {
	xVel += x;
}

void Sprite::SetYVelBy(float y) {
	yVel += y;
}

void Sprite::SetXYVelBy(float x, float y) {
	xVel += x;
	yVel += y;
}

void Sprite::MoveRight() {
	xPos += xVel;
}

void Sprite::MoveLeft() {
	xPos -= xVel;
}

void Sprite::MoveUp() {
	yPos += yVel;
}

void Sprite::MoveDown() {
	yPos -= yVel;
}

int Sprite::GetWidth() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.GetID());
	glLoadIdentity();
	return texture.GetWidth();
}

int Sprite::GetHeight() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.GetID());
	glLoadIdentity();
	return texture.GetHeight();
}

void Sprite::Render() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.GetID());
	glLoadIdentity();

	glTranslatef(xPos, yPos, 0);
	glRotatef(rot, 0, 0, 1);
	glScalef(xScale, yScale, 1);

	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);		glVertex2f(0, 0);
	glTexCoord2f(1, 0);		glVertex2f(texture.GetWidth(), 0);
	glTexCoord2f(1, 1);		glVertex2f(texture.GetWidth(), texture.GetHeight());
	glTexCoord2f(0, 1);		glVertex2f(0, texture.GetHeight());

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Sprite::Render(int width, int height) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.GetID());
	glLoadIdentity();

	glTranslatef(xPos, yPos, 0);
	glRotatef(rot, 0, 0, 1);
	glScalef(xScale, yScale, 1);

	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);		glVertex2f(0, 0);
	glTexCoord2f(1, 0);		glVertex2f(width, 0);
	glTexCoord2f(1, 1);		glVertex2f(width, height);
	glTexCoord2f(0, 1);		glVertex2f(0, height);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

