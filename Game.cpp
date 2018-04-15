#include <iostream>
#include "Engine\Engine.h"
#include "Engine\Graphics\Sprite.h"
#include "Engine\Input\Mouse.h"
#include "Engine\Input\Keyboard.h"
#include "Player.h"
#include "Map.h"

using namespace std;

int main() {

	Engine engine;
	engine.Init("Test");
	Sprite testSprite = Sprite("Assets/Art/box.png", 500, 0);
	Sprite secondSprite = Sprite("Assets/Art/scithersword.png", 2500, 0);
	Player player = Player();
	Map map = Map("Assets/Maps/map1.txt");
	//map.LoadMap("Assets/Maps/map1.txt");

	testSprite.SetScaleTo(1);
	secondSprite.SetScaleTo(1);


	while (true) {

		

		engine.Update();
		player.Update();
		testSprite.Update();
		secondSprite.Update();


		engine.BeginRender();
		map.Render();
		testSprite.Render();
		secondSprite.Render();
		player.Render();
		
		
		engine.EndRender();
	}

	return 0;
}