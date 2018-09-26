#pragma once

/*
This Texture class was copied from another programmer who made a video on Youtube on how to make a game.
We DID NOT take this class into consideration when counting the lines of code.

This was programmed by Progrematic

Video: https://www.youtube.com/watch?v=4R5vSIZxr0M
*/

#include "GLFW\glfw3.h"
#include "simple-opengl-image-library-master\src\SOIL.h"

#include <iostream>
#include <string>
using namespace std;

class Texture {

public:
	Texture();
	Texture(int _id);
	Texture(string path);

	int GetID();
	int GetWidth();
	int GetHeight();

private:
	bool GetTextureParams();
	int id;
	int width;
	int height;
};