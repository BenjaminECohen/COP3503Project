#include "Engine.h"
#include "Input\Mouse.h"
#include "Input\Keyboard.h"

/*
This Engine class was copied from another programmer who made a video on Youtube on how to make a game.
We DID NOT take this class into consideration when counting the lines of code.\

This was programmed by Progrematic

Video: https://www.youtube.com/watch?v=4R5vSIZxr0M
*/

int Engine::SCREEN_WIDTH = 1024;
int Engine::SCREEN_HEIGHT = 768;
GLFWwindow* Engine::window = NULL;

Engine::Engine() {

}

Engine::~Engine() {

}

bool Engine::Init(const char* title) {
	if (!glfwInit()) {
		cout << "Error Initializing GLFW" << endl;
		return false;
	}

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title, NULL, NULL);
	if (window == NULL) {
		cout << "Error creating window" << endl;
		return false;
	}

	//OpenGL setup
	glfwMakeContextCurrent(window);
	int width;
	int height;
	glfwGetFramebufferSize(window, &width, &height);
	glfwSwapInterval(1);

	glfwSetCursorPosCallback(window, Mouse::MousePosCallback);
	glfwSetMouseButtonCallback(window, Mouse::ButtonCallback);
	glfwSetKeyCallback(window, Keyboard::KeyCallBack);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int xPos = (mode->width - SCREEN_WIDTH)/2;
	int yPos = (mode->height - SCREEN_HEIGHT)/2;
	glfwSetWindowPos(window, xPos, yPos);

	//GL setup
	//viewport

	glViewport(10, 10, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -10, 10);
	glDepthRange(-10, 10);
	glMatrixMode(GL_MODELVIEW);

	//alpha blending
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void Engine::Update() {
	glfwPollEvents();
}

void Engine::BeginRender() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor4f(1, 1, 1, 1);
	
	
}

void Engine::EndRender() {
	glfwSwapBuffers(window);
}