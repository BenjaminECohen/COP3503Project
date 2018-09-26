#pragma once


class GameState {

public:
	static void setGameState(int state);
	static int getGameState();
	static bool changeStates;
	static bool restartStates;
	
private:
	static int gameState;

};