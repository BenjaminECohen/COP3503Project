#include "Texture.h"

/*
This Texture class was copied from another programmer who made a video on Youtube on how to make a game.
We DID NOT take this class into consideration when counting the lines of code.

This was programmed by Progrematic

Video: https://www.youtube.com/watch?v=4R5vSIZxr0M
*/


Texture::Texture() {
	id = -1;
}

Texture::Texture(int _id) {
	id = _id;
}

Texture::Texture(string path) {
	id = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y);
	if (!GetTextureParams()) {
		cout << "Error Loading Image: " << path << endl;
	}
}

int Texture::GetID() {
	return id;
}

int Texture::GetWidth() {
	return width;
}

int Texture::GetHeight() {
	return height;
}

bool Texture::GetTextureParams() {
	

	if (id > 0) {
		int mipLevel = 0;
		glBindTexture(GL_TEXTURE_2D, id);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_HEIGHT, &height);
		return true;
	}
	return false;
}