#pragma once
#include "GLFW\glfw3.h"
#pragma comment(lib, "opengl32.lib")

/*
This Engine class was copied from another programmer who made a video on Youtube on how to make a game.
We DID NOT take this class into consideration when counting the lines of code.\

This was programmed by Progrematic

Video: https://www.youtube.com/watch?v=4R5vSIZxr0M
*/

#include <iostream>

using namespace std;

class Engine
{
public:
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;

	Engine();
	~Engine();

	bool Init(const char* title);

	void Update();
	void BeginRender();
	void EndRender();


private:

	static GLFWwindow* window;

};


//#endif