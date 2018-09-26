#include "Camera.h"

//Camera is a static class that stores the coordinates of the bottom left of the veiwable screen
//only changed in player class


float Camera::xCoord = 0;
float Camera::yCoord = 0;

void Camera::setXCoord(float xCoord) {
	Camera::xCoord = xCoord;
}

void Camera::setYCoord(float yCoord) {
	Camera::yCoord = yCoord;
}

float Camera::getXCoord() {
	return Camera::xCoord;
}

float Camera::getYCoord() {
	return Camera::yCoord;
}
