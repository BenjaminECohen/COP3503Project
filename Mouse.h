#pragma once

#include "GLFW\glfw3.h"

/*
This Mouse class was copied from another programmer who made a video on Youtube on how to make a game.
We DID NOT take this class into consideration when counting the lines of code.

This was programmed by Progrematic

Video: https://www.youtube.com/watch?v=Kw4fKVsbrjw
*/

class Mouse {
public:
	static void MousePosCallback(GLFWwindow* window, double _x, double _y);
	static void ButtonCallback(GLFWwindow* window, int button, int action, int mod);

	static double GetMouseX();
	static double GetMouseY();

	static bool ButtonDown(int button);
	static bool ButtonUp(int button);
	static bool Button(int button);

private:
	static double x;
	static double y;

	static bool buttons[];
	static bool buttonsDown[];
	static bool buttonsUp[];
};