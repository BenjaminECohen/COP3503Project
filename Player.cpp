#include "Player.h"

Player::Player() {
	xPos = 0;
	yPos = 0;
	xVel = 0;
	yVel = 0;
	cameraCoordX = 0;
	cameraCoordY = 0;
	playerSprite = Sprite("Assets/Art/bad-character.png", xPos, yPos);
	playerSprite.SetScaleTo(1);
}

Player::Player(float xPos, float yPos) {
	this->xPos = xPos;
	this->yPos = yPos;
	xVel = 0;
	yVel = 0;
	playerSprite = Sprite("Assets/Art/bad-character.png", xPos, yPos);
	playerSprite.SetScaleTo(1);
}

void Player::Render() {
	playerSprite.Render();
}

void Player::moveCamera() {

	if (xPos - cameraCoordX > Engine::SCREEN_WIDTH*(.66)) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(xPos - Engine::SCREEN_WIDTH*(.66), xPos + Engine::SCREEN_WIDTH*(.33), 0, Engine::SCREEN_HEIGHT, -10, 10);
		glMatrixMode(GL_MODELVIEW);
		cameraCoordX = xPos - Engine::SCREEN_WIDTH*(.66);
	}
	if (xPos - cameraCoordX < Engine::SCREEN_WIDTH*(.33) && xPos > Engine::SCREEN_WIDTH*(.33)) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(xPos - Engine::SCREEN_WIDTH*(.33), xPos + Engine::SCREEN_WIDTH*(.66), 0, Engine::SCREEN_HEIGHT, -10, 10);
		glMatrixMode(GL_MODELVIEW);
		cameraCoordX = xPos - Engine::SCREEN_WIDTH*(.33);
	}

}



void Player::Update() {
	keyHandle();
	moveCamera();

	playerSprite.SetPosTo(xPos, yPos);
	xPos += xVel;
	yPos += yVel;
	checkCollisions();
	slowDown();
}

void Player::keyHandle() {
	if (Keyboard::KeyDown(GLFW_KEY_W)) {
		if (hasJump) {
			if (yVel != 0) {
				hasJump = false;
			}
			yVel = .8;
		}
	}
	if (Keyboard::Key(GLFW_KEY_A)) {
		xVel = -.7;
	}
	if (Keyboard::Key(GLFW_KEY_D)) {
		xVel = .7;
	}
}

void Player::checkCollisions() {
	if (yPos < 1) {
		yVel = 0;
		hasJump = true;
	}
	else {
		yVel -= .003;
	}
}

void Player::slowDown() {
	if (xVel >= .005 || xVel <= -.005) {
		if (xVel < 0) {
			xVel += .0015;
		}
		if (xVel > 0) {
			xVel -= .0015;
		}
	}
	else {
		xVel = 0;
	}
}