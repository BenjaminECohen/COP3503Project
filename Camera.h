#pragma once
class Camera {
public:
	static void setXCoord(float xCoord);
	static void setYCoord(float yCoord);
	static float getXCoord();
	static float getYCoord();

private:
	static float xCoord;
	static float yCoord;
};