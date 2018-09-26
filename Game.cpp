#include "Player.h"
#include "Map.h"
#include "GameState.h"
#include "Background.h"
#include <windows.h>
using namespace std;

int main() {

	Engine engine;
	engine.Init("JOBASM");
	Player player;
	Map map;
	Background background;

	while (true) {
		GameState::setGameState(2);
		switch (GameState::getGameState()) {
		case 1:
			//loads in player, map 1, and background 1
			PlaySound("Assets/Sound/JobasmOST.wav", NULL, SND_LOOP | SND_ASYNC | SND_NOSTOP);
			map.LoadMap("Assets/Maps/map1.txt");
			player = Player(0, 100, map.blockArray, map.basicEnemyArray);
			map.setProjectileArray(player.projectileArray);
			background = Background("Assets/Art/Desert1.png");
			break;
		case 2:
			//loads in player, map 2, and background 2
			PlaySound(0, NULL, NULL);
			PlaySound("Assets/Sound/LevelSong.wav", NULL, SND_LOOP | SND_ASYNC | SND_NOSTOP);
			map.LoadMap("Assets/Maps/map2.txt");
			player = Player(0, 100, map.blockArray, map.basicEnemyArray);
			map.setProjectileArray(player.projectileArray);
			background = Background("Assets/Art/Desert2.png");
			break;
		case 3:
			//loads in player, map 3, and background 3
			PlaySound(0, NULL, NULL);
			PlaySound("Assets/Sound/JobasmOST.wav", NULL, SND_LOOP | SND_ASYNC | SND_NOSTOP);
			map.LoadMap("Assets/Maps/map3.txt");
			player = Player(0, 100, map.blockArray, map.basicEnemyArray);
			map.setProjectileArray(player.projectileArray);
			background = Background("Assets/Art/Desert3.png");
			break;
		case 4:
			//loads in player, map 4, and background 4
			PlaySound(0, NULL, NULL);
			PlaySound("Assets/Sound/BossMusicAmIRight.wav", NULL, SND_LOOP | SND_ASYNC | SND_NOSTOP);
			map.LoadMap("Assets/Maps/map4.txt");
			player = Player(1000, 100, map.blockArray, map.basicEnemyArray);
			map.setProjectileArray(player.projectileArray);
			background = Background("Assets/Art/full_background.png");

			break;
		case 5:
			//loads in final image credits screen, exits on  escape press
			background = Background("Assets/Art/Credits.png");
			player = Player(0, 0, map.blockArray, map.basicEnemyArray);
			engine.Update();
			player.Update();
			map.Update();
			background.Update();
			engine.BeginRender();
			background.Render();
			engine.EndRender();
			while (true) {
				engine.Update();
				if (Keyboard::KeyDown(GLFW_KEY_ESCAPE)) {
					break;
				}
			}
			
			return 0;
			break;
		default:
			
			break;
		}

		GameState::restartStates = false;
		GameState::changeStates = false;

		while (true) {
			//updates all objects and updates arrays of projectiles and enemies to all objects that need them
			engine.Update();
			player.Update();
			map.Update();
			background.Update();
			map.setProjectileArray(player.projectileArray);
			player.setBasicEnemyArray(map.basicEnemyArray);
			player.setChaseEnemyArray(map.chaseEnemyArray);
			player.setTurretEnemyArray(map.turretEnemyArray);
			player.setBoss(map.bigBoss);
			map.setPlayerPos(player.getXPos(),  player.getYPos());

			engine.BeginRender();

			//renders background, map,  and player
			//map class renders all enemies and their projectiles
			//player class renders player and player projectiles
			background.Render();
			map.Render();
			player.Render();

			engine.EndRender();

			//checks for next level conditions
			if (GameState::changeStates) {
				GameState::setGameState(GameState::getGameState() + 1);
				break;
			}

			if (GameState::restartStates) {
				break;
			}
		}
	}

	return 0;
}