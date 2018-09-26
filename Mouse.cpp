#include "Mouse.h"

/*
This Mouse class was copied from another programmer who made a video on Youtube on how to make a game.
We DID NOT take this class into consideration when counting the lines of code.

This was programmed by Progrematic

Video: https://www.youtube.com/watch?v=Kw4fKVsbrjw
*/

double Mouse::x = 0;
double Mouse::y = 0;

bool Mouse::buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::buttonsDown[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::buttonsUp[GLFW_MOUSE_BUTTON_LAST] = { 0 };

void Mouse::MousePosCallback(GLFWwindow* window, double _x, double _y) {
	int width;
	int height;
	glfwGetFramebufferSize(window, &width, &height);

	
	x = _x;
	y = height - _y;
}

void Mouse::ButtonCallback(GLFWwindow* window, int button, int action, int mods) {

	if (button < 0) {
		return;
	}

	if (action != GLFW_RELEASE && !buttons[button]) {
		buttonsDown[button] = true;
		buttonsUp[button] = false;
	}

	if (action == GLFW_RELEASE && buttons[button]) {
		buttonsDown[button] = false;
		buttonsUp[button] = true;
	}

	buttons[button] = action != GLFW_RELEASE;

}

double Mouse::GetMouseX() {
	return x;
}
double Mouse::GetMouseY() {
	return y;
}

bool Mouse::ButtonDown(int button) {

	bool x = buttonsDown[button];
	buttonsDown[button] = false;
	return x;

}

bool Mouse::ButtonUp(int button) {

	bool x = buttonsUp[button];
	buttonsUp[button] = false;
	return x;

}

bool Mouse::Button(int button) {

	return buttons[button];

}