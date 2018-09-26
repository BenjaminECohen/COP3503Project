#pragma once

#include "GLFW\glfw3.h"

/*
This Keyboard class was copied from another programmer who made a video on Youtube on how to make a game.
We DID NOT take this class into consideration when counting the lines of code.

This was programmed by Progrematic

Video: https://www.youtube.com/watch?v=Kw4fKVsbrjw
*/

class Keyboard {
public:
	static void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);

	static bool Key(int key);
	static bool KeyDown(int key);
	static bool KeyUp(int key);
private:
	static bool keys[];
	static bool keysDown[];
	static bool keysUp[];

};
	

