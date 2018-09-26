#include "GameState.h"

int GameState::gameState = 1;
bool GameState::changeStates = false;
bool GameState::restartStates = false;

void GameState::setGameState(int state) {
	gameState = state;
}

int GameState::getGameState() {
	return gameState;
}