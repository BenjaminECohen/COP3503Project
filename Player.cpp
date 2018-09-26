#include "Player.h"

//default constructor
Player::Player() {
	xPos = 0;
	yPos = 0;
	xVel = 0;
	yVel = 0;
	Camera::setXCoord(0);
	Camera::setYCoord(0);
	playerSprite = Sprite("Assets/Art/CowboyRidingSegway.png", xPos, yPos);
	playerSprite.SetScaleTo(1);
	playerSpriteFlip = Sprite("Assets/Art/CowboyRidingSegwayFlip.png", xPos, yPos);
	playerSpriteFlip.SetScaleTo(1);
	health = 0;
}

//constructor used throughout program, gives a starting x position, y position, the block  array for the level, and enemy array
Player::Player(float xPos, float yPos, std::array<Block, 100> blockArray, std::array<BasicEnemy, 5> basicEnemyArray) {
	this->xPos = xPos;
	this->yPos = yPos;
	xVel = 0;
	yVel = 0;
	Camera::setXCoord(0);
	Camera::setYCoord(0);
	playerSprite = Sprite("Assets/Art/CowboyRidingSegway.png", xPos, yPos);
	playerSprite.SetScaleTo(1);
	playerSpriteFlip = Sprite("Assets/Art/CowboyRidingSegwayFlip.png", xPos, yPos);
	playerSpriteFlip.SetScaleTo(1);
	heart1 = Sprite("Assets/Art/heart.png", Camera::getXCoord(), 650);
	heart2 = Sprite("Assets/Art/heart.png", Camera::getXCoord() + 30, 650);
	heart3 = Sprite("Assets/Art/heart.png", Camera::getXCoord() + 60, 650);
	heart1.SetScaleTo(1);
	heart2.SetScaleTo(1);
	heart3.SetScaleTo(1);
	this->blockArray = blockArray;
	this->basicEnemyArray = basicEnemyArray;
	
	//sets initial camera position based  on player starting position
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(Camera::getXCoord(), Camera::getYCoord() + Engine::SCREEN_WIDTH, 0, Engine::SCREEN_HEIGHT, -10, 10);
	glMatrixMode(GL_MODELVIEW);

	//resets projectile array
	for (int i = 0; i < projectileArray.size(); i++) {
		projectileArray[i].exists = false;
	}
	health = 3;

	//time invulnerable after hit, in game ticks
	vulTime = 500;
}

void Player::Render() {
	//if vulnerable, flash by only rendering player 2/3 of frames
	if (vulTime % 3 != 0) {
		if (xVel >= 0)
		{
			playerSprite.Render();
		}
		else
		{
			playerSpriteFlip.Render();
		}
		
	}
	
	//render existing projectiles in projectile array
	for (int i = 0; i < projectileArray.size(); i++) {
		if (projectileArray[i].exists) {
			projectileArray[i].Render();
		}
	}

	//render health stats
	if (health == 3) {
		heart1.Render();
		heart2.Render();
		heart3.Render();
	}
	if (health == 2) {
		heart1.Render();
		heart2.Render();
	}
	if (health == 1) {
		heart1.Render();
	}
}

void Player::moveCamera() {

	//tracks player, if he moves past 2/3 to the right of the screen, move with him, 
	//if he moves before  1/3 of the screen, move with him to the  left
	if (xPos < 3755) {
		if (xPos - Camera::getXCoord() > Engine::SCREEN_WIDTH*(.66)) {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(xPos - Engine::SCREEN_WIDTH*(.66), xPos + Engine::SCREEN_WIDTH*(.33), 0, Engine::SCREEN_HEIGHT, -10, 10);
			glMatrixMode(GL_MODELVIEW);
			Camera::setXCoord(xPos - Engine::SCREEN_WIDTH*(.66));
		}
		if (xPos - Camera::getXCoord() < Engine::SCREEN_WIDTH*(.33) && xPos > Engine::SCREEN_WIDTH*(.33)) {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(xPos - Engine::SCREEN_WIDTH*(.33), xPos + Engine::SCREEN_WIDTH*(.66), 0, Engine::SCREEN_HEIGHT, -10, 10);
			glMatrixMode(GL_MODELVIEW);
			Camera::setXCoord(xPos - Engine::SCREEN_WIDTH*(.33));
		}
	}

}



void Player::Update() {
	//check inputs
	keyHandle();
	//move camera based on his position
	moveCamera();

	//update projectlie array
	for (int i = 0; i < projectileArray.size(); i++) {
		if (projectileArray[i].exists) {
			projectileArray[i].Update();
		}
	}

	//sets position of heart sprites to  track with camera
	heart1.SetPosTo(Camera::getXCoord(), 680);
	heart2.SetPosTo(Camera::getXCoord() + 30, 680);
	heart3.SetPosTo(Camera::getXCoord() + 60, 680);

	//sets sprite to current position
	playerSprite.SetPosTo(xPos, yPos);
	//sets flipped sprite to current position
	playerSpriteFlip.SetPosTo(xPos, yPos);

	//adds velocity to current position
	if (xPos >= 0 && xPos <= 3755) {
		xPos += xVel;
	}
	else if (xPos >= 0) {
		xPos += 1;
	}
	else {
		xPos -= 1;
	}
	yPos += yVel;

	//checks collisions with ground, enemies, and enemy projectiles
	checkCollisions();

	//adds small deceleration time to x velocity
	slowDown();

	//restarts state if dead
	if (health < 1) {
		GameState::restartStates = true;
	}

	//subtracts from invulnerable time if hit
	if (vulnerable == false) {
		vulTime -= 1;
	}

	//if invulnerability time is over, sets time back to 500, makes player vunerable to attack again
	if (vulTime == 0) {
		vulTime = 500;
		vulnerable = true;
	}
}

//sets array of basic enemies for player collisions
void Player::setBasicEnemyArray(std::array<BasicEnemy, 5> basicEnemyArray) {
	this->basicEnemyArray = basicEnemyArray;
}

//sets array of chase enemies for player collisions
void Player::setChaseEnemyArray(std::array<ChaseEnemy, 5> chaseEnemyArray) {
	this->chaseEnemyArray = chaseEnemyArray;
}

//sets array of turret enemies for player collisions
void Player::setTurretEnemyArray(std::array<TurretEnemy, 5> turretEnemyArray) {
	this->turretEnemyArray = turretEnemyArray;
}

//sets boss enemy for player collisions
void Player::setBoss(BigBoss bigBoss) {
	this->bigBoss = bigBoss;
}

//adds projectile to projectile array if there is place
//max of 5 player projectiles on screen at once
void Player::shoot() {
	for (int i = 0; i < projectileArray.size(); i++) {
		if (!projectileArray[i].exists) {
			mciSendString("play Assets/Sound/GunShot2.wav", NULL, 0, NULL);
			projectileArray[i] = Projectile(xPos + playerSprite.GetWidth() / 2, 
								yPos + playerSprite.GetHeight() / 2, 
								Mouse::GetMouseX() + Camera::getXCoord(), 
								Mouse::GetMouseY() + Camera::getYCoord(), 
								1, 
								"Assets/Art/PlayerBullet.png", 
								10, 
								10);
			break;
		}
	}
}

float Player::getHeight() {
	return playerSprite.GetHeight();
}

float Player::getWidth() {
	return playerSprite.GetWidth();
}

float Player::getXPos() {
	return xPos;
}

float Player::getYPos() {
	return yPos;
}

//handles input from user
void Player::keyHandle() {
	
	if (Mouse::ButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
		shoot();
	}


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


void Player::getHurt(){
	health -= 1;
	vulnerable = false;
}

//checks all collisions, also handles gravity
void Player::checkCollisions() {


	//adds small value to y velocity each frame, simulates real gravity
	//has terminal falling velocity of 1.5 pixels per frame
	if (yPos < 1) {
		yVel = 0;
		hasJump = true;
	}
	else {
		if (yVel <= -1.5) {
			yVel = -1.5;
		}
		else {
			yVel -= .003;
		}
	}


	//checks collisions of blocks with player
	//checks if any part of player sprite is inside any part of the blocks sprite
	for (int i = 0; i < blockArray.size(); i++) {

		if (yPos + playerSprite.GetHeight() > blockArray[i].getYPos() && yPos < blockArray[i].getYPos() + 64) {
			if (xPos > blockArray[i].getXPos() + 32) {
				if ((yPos + playerSprite.GetHeight()) > (blockArray[i].getYPos())) {
					if ((xPos + xVel) <= (blockArray[i].getXPos() + 64)) {
						xVel = 0;
						xPos = (blockArray[i].getXPos() + 64);
						if (blockArray[i].getBlockType() == 2) {
							mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
							GameState::restartStates = true;
							health = 0;
						}
						if (blockArray[i].getBlockType() == 3) {
							GameState::changeStates = true;
						}
					}
				}
			}
			else {
				if (yPos < blockArray[i].getYPos() + 64) {
					if ((xPos + xVel + playerSprite.GetWidth()) > (blockArray[i].getXPos())) {
						xVel = 0;
						xPos = (blockArray[i].getXPos()) - playerSprite.GetWidth();
						if (blockArray[i].getBlockType() == 2) {
							mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
							GameState::restartStates = true;
							health = 0;
						}
						if (blockArray[i].getBlockType() == 3) {
							GameState::changeStates = true;
						}
					}
				}
			}
		}

		if (xPos + playerSprite.GetWidth() > blockArray[i].getXPos() && xPos < blockArray[i].getXPos() + 64) {
			if (yPos > blockArray[i].getYPos() + 32) {
				if ((xPos + playerSprite.GetWidth()) > (blockArray[i].getXPos())) {
					if ((yPos + yVel) <= (blockArray[i].getYPos() + 64)) {
						yVel = 0;
						hasJump = true;
						yPos = (blockArray[i].getYPos() + 64);
						if (blockArray[i].getBlockType() == 2) {
							mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
							GameState::restartStates = true;
							health = 0;
						}
						if (blockArray[i].getBlockType() == 3) {
							GameState::changeStates = true;
						}
					}
				}
			}
			else {
				if (xPos < blockArray[i].getXPos() + 64) {
					if ((yPos + yVel + playerSprite.GetHeight()) > (blockArray[i].getYPos())) {
						yVel = 0;
						yPos = (blockArray[i].getYPos()) - playerSprite.GetHeight();
						if (blockArray[i].getBlockType() == 2) {
							mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
							GameState::restartStates = true;
							health = 0;
						}
						if (blockArray[i].getBlockType() == 3) {
							GameState::changeStates = true;
						}
					}
				}
			}
		}
	}
		
	//checks all enemy attacks collision	
	if (vulnerable) {

		//checks collisions of basic enemies with player
		//checks if any part of player sprite is inside any part of the basic enemy's sprite
		//plays hurt sound if hit
		for (int i = 0; i < basicEnemyArray.size(); i++) {
			if (basicEnemyArray[i].exists) {
				if (yPos + playerSprite.GetHeight() > basicEnemyArray[i].getYPos() && yPos < basicEnemyArray[i].getYPos() + basicEnemyArray[i].getHeight()) {
					if (xPos > basicEnemyArray[i].getXPos() + basicEnemyArray[i].getWidth() / 2) {
						if ((yPos + playerSprite.GetHeight()) > (basicEnemyArray[i].getYPos())) {
							if ((xPos + xVel) <= (basicEnemyArray[i].getXPos() + basicEnemyArray[i].getWidth())) {
								mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
								//get hurt
								getHurt();

								break;
							}
						}
					}
					else {
						if (yPos < basicEnemyArray[i].getYPos() + basicEnemyArray[i].getHeight()) {
							if ((xPos + xVel + playerSprite.GetWidth()) > (basicEnemyArray[i].getXPos())) {
								mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
								//get hurt
								getHurt();

								break;
							}
						}
					}
				}
				else if (xPos + playerSprite.GetWidth() > basicEnemyArray[i].getXPos() && xPos < basicEnemyArray[i].getXPos() + basicEnemyArray[i].getWidth()) {
					if (yPos > basicEnemyArray[i].getYPos() + basicEnemyArray[i].getHeight() / 2) {
						if ((xPos + playerSprite.GetWidth()) > (basicEnemyArray[i].getXPos())) {
							if ((yPos + yVel) <= (basicEnemyArray[i].getYPos() + basicEnemyArray[i].getHeight())) {
								mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
								//get hurt
								getHurt();

								break;
							}
						}
					}
					else {
						if (xPos < basicEnemyArray[i].getXPos() + basicEnemyArray[i].getWidth()) {
							if ((yPos + yVel + playerSprite.GetHeight()) > (basicEnemyArray[i].getYPos())) {
								mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
								//get hurt
								getHurt();

								break;
							}
						}
					}
				}
			}
		}


		//checks collisions of basic enemies with player
		//checks if any part of player sprite is inside any part of the blocks sprite
		//plays hurt sound if hit
		for (int i = 0; i < chaseEnemyArray.size(); i++) {
			if (chaseEnemyArray[i].exists) {
				if (yPos + playerSprite.GetHeight() > chaseEnemyArray[i].getYPos() && yPos < chaseEnemyArray[i].getYPos() + chaseEnemyArray[i].getHeight()) {
					if (xPos > chaseEnemyArray[i].getXPos() + chaseEnemyArray[i].getWidth() / 2) {
						if ((yPos + playerSprite.GetHeight()) > (chaseEnemyArray[i].getYPos())) {
							if ((xPos + xVel) <= (chaseEnemyArray[i].getXPos() + chaseEnemyArray[i].getWidth())) {
								mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
								//get hurt
								getHurt();

								break;
							}
						}
					}
					else {
						if (yPos < chaseEnemyArray[i].getYPos() + chaseEnemyArray[i].getHeight()) {
							if ((xPos + xVel + playerSprite.GetWidth()) >(chaseEnemyArray[i].getXPos())) {
								mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
								//get hurt
								getHurt();

								break;
							}
						}
					}
				}
				else if (xPos + playerSprite.GetWidth() > chaseEnemyArray[i].getXPos() && xPos < chaseEnemyArray[i].getXPos() + chaseEnemyArray[i].getWidth()) {
					if (yPos > chaseEnemyArray[i].getYPos() + chaseEnemyArray[i].getHeight() / 2) {
						if ((xPos + playerSprite.GetWidth()) > (chaseEnemyArray[i].getXPos())) {
							if ((yPos + yVel) <= (chaseEnemyArray[i].getYPos() + chaseEnemyArray[i].getHeight())) {
								mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
								//get hurt
								getHurt();

								break;
							}
						}
					}
					else {
						if (xPos < chaseEnemyArray[i].getXPos() + chaseEnemyArray[i].getWidth()) {
							if ((yPos + yVel + playerSprite.GetHeight()) >(chaseEnemyArray[i].getYPos())) {
								mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
								//get hurt
								getHurt();

								break;
							}
						}
					}
				}
			}
		}
		//checks collisions of turret enemys' projectiles with player
		//checks if any part of player sprite is inside any part of the projectile sprite
		//plays hurt sound if hit
		for (int i = 0; i < turretEnemyArray.size(); i++) {
			if (turretEnemyArray[i].exists) {
				if (yPos + playerSprite.GetHeight() > turretEnemyArray[i].projectileArray[0].getYPos() && yPos < turretEnemyArray[i].projectileArray[0].getYPos() + turretEnemyArray[i].projectileArray[0].getHeight()) {
					if (xPos > turretEnemyArray[i].projectileArray[0].getXPos() + turretEnemyArray[i].projectileArray[0].getWidth() / 2) {
						if ((yPos + playerSprite.GetHeight()) > (turretEnemyArray[i].projectileArray[0].getYPos())) {
							if ((xPos + xVel) <= (turretEnemyArray[i].projectileArray[0].getXPos() + turretEnemyArray[i].projectileArray[0].getWidth())) {
								mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
								//get hurt
								getHurt();

								break;
							}
						}
					}
					else {
						if (yPos < turretEnemyArray[i].projectileArray[0].getYPos() + turretEnemyArray[i].projectileArray[0].getHeight()) {
							if ((xPos + xVel + playerSprite.GetWidth()) >(turretEnemyArray[i].projectileArray[0].getXPos())) {
								mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
								//get hurt
								getHurt();

								break;
							}
						}
					}
				}
				else if (xPos + playerSprite.GetWidth() > turretEnemyArray[i].projectileArray[0].getXPos() && xPos < turretEnemyArray[i].projectileArray[0].getXPos() + turretEnemyArray[i].projectileArray[0].getWidth()) {
					if (yPos > turretEnemyArray[i].projectileArray[0].getYPos() + turretEnemyArray[i].projectileArray[0].getHeight() / 2) {
						if ((xPos + playerSprite.GetWidth()) > (turretEnemyArray[i].projectileArray[0].getXPos())) {
							if ((yPos + yVel) <= (turretEnemyArray[i].projectileArray[0].getYPos() + turretEnemyArray[i].projectileArray[0].getHeight())) {
								mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
								//get hurt
								getHurt();

								break;
							}
						}
					}
					else {
						if (xPos < turretEnemyArray[i].projectileArray[0].getXPos() + turretEnemyArray[i].projectileArray[0].getWidth()) {
							if ((yPos + yVel + playerSprite.GetHeight()) >(turretEnemyArray[i].projectileArray[0].getYPos())) {
								mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
								//get hurt
								getHurt();

								break;
							}
						}
					}
				}
			}
		}
		//checks collisions of boss with player
		//checks if any part of player sprite is inside any part of the boss sprite
		//plays hurt sound if hit
		if (bigBoss.exists) {
			if (yPos + playerSprite.GetHeight() > bigBoss.getYPos() && yPos < bigBoss.getYPos() + bigBoss.getHeight()) {
				if (xPos > bigBoss.getXPos() + bigBoss.getWidth() / 2) {
					if ((yPos + playerSprite.GetHeight()) > (bigBoss.getYPos())) {
						if ((xPos + xVel) <= (bigBoss.getXPos() + bigBoss.getWidth())) {
							mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
							//get hurt
							getHurt();

						}
					}
				}
				else {
					if (yPos < bigBoss.getYPos() + bigBoss.getHeight()) {
						if ((xPos + xVel + playerSprite.GetWidth()) >(bigBoss.getXPos())) {
							mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
							//get hurt
							getHurt();
						}
					}
				}
			}
			else if (xPos + playerSprite.GetWidth() > bigBoss.getXPos() && xPos < bigBoss.getXPos() + bigBoss.getWidth()) {
				if (yPos > bigBoss.getYPos() + bigBoss.getHeight() / 2) {
					if ((xPos + playerSprite.GetWidth()) > (bigBoss.getXPos())) {
						if ((yPos + yVel) <= (bigBoss.getYPos() + bigBoss.getHeight())) {
							mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
							//get hurt
							getHurt();

						}
					}
				}
				else {
					if (xPos < bigBoss.getXPos() + bigBoss.getWidth()) {
						if ((yPos + yVel + playerSprite.GetHeight()) >(bigBoss.getYPos())) {
							mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
							//get hurt
							getHurt();

						}
					}
				}
			}
		}
		//checks collisions of boss projectiles with player
		//checks if any part of boss's projectles sprite is inside any part of the player sprite
		//plays hurt sound if hit
		if (bigBoss.exists) {
			if (yPos + playerSprite.GetHeight() > bigBoss.projectileArray[0].getYPos() && yPos < bigBoss.projectileArray[0].getYPos() + bigBoss.projectileArray[0].getHeight()) {
				if (xPos > bigBoss.projectileArray[0].getXPos() + bigBoss.projectileArray[0].getWidth() / 2) {
					if ((yPos + playerSprite.GetHeight()) > (bigBoss.projectileArray[0].getYPos())) {
						if ((xPos + xVel) <= (bigBoss.projectileArray[0].getXPos() + bigBoss.projectileArray[0].getWidth())) {
							mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
							//get hurt
							getHurt();

						
						}
					}
				}
				else {
					if (yPos < bigBoss.projectileArray[0].getYPos() + bigBoss.projectileArray[0].getHeight()) {
						if ((xPos + xVel + playerSprite.GetWidth()) >(bigBoss.projectileArray[0].getXPos())) {
							mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
							//get hurt
							getHurt();

						
						}
					}
				}
			}
			else if (xPos + playerSprite.GetWidth() > bigBoss.projectileArray[0].getXPos() && xPos < bigBoss.projectileArray[0].getXPos() + bigBoss.projectileArray[0].getWidth()) {
				if (yPos > bigBoss.projectileArray[0].getYPos() + bigBoss.projectileArray[0].getHeight() / 2) {
					if ((xPos + playerSprite.GetWidth()) > (bigBoss.projectileArray[0].getXPos())) {
						if ((yPos + yVel) <= (bigBoss.projectileArray[0].getYPos() + bigBoss.projectileArray[0].getHeight())) {
							mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
							//get hurt
							getHurt();

						
						}
					}
				}
				else {
					if (xPos < bigBoss.projectileArray[0].getXPos() + bigBoss.projectileArray[0].getWidth()) {
						if ((yPos + yVel + playerSprite.GetHeight()) >(bigBoss.projectileArray[0].getYPos())) {
							mciSendString("play Assets/Sound/Hurt_Scream.wav", NULL, 0, NULL);
							//get hurt
							getHurt();

							
						}
					}
				}
			}
		}
	}
}

//slows down player if not holding left or right directional key
void Player::slowDown() {
	if (xVel >= .005 || xVel <= -.005) {
		if (xVel < 0) {
			xVel += .01;
		}
		if (xVel > 0) {
			xVel -= .01;
		}
	}
	else {
		xVel = 0;
	}
}