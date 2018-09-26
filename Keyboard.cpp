#include "Keyboard.h"

/*
This Keyboard class was copied from another programmer who made a video on Youtube on how to make a game.
We DID NOT take this class into consideration when counting the lines of code.

This was programmed by Progrematic

Video: https://www.youtube.com/watch?v=Kw4fKVsbrjw
*/

bool Keyboard::keys[GLFW_KEY_LAST] = { 0 };
bool Keyboard::keysDown[GLFW_KEY_LAST] = { 0 };
bool Keyboard::keysUp[GLFW_KEY_LAST] = { 0 };

void Keyboard::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key < 0) {
		return;
	}
	if (action != GLFW_RELEASE && keys[key] == false) {
		keysDown[key] = true;
		keysUp[key] = false;
	}

	if (action == GLFW_RELEASE && keys[key] == true) {
		keysDown[key] = false;
		keysUp[key] = true;
	}

	keys[key] = action != GLFW_RELEASE;
}

bool Keyboard::KeyDown(int key) {
	bool x = keysDown[key];
	keysDown[key] = false;
	return x;
}

bool Keyboard::KeyUp(int key) {
	bool x = keysUp[key];
	keysUp[key] = false;
	return x;
}

bool Keyboard::Key(int key) {
	return keys[key];
}
