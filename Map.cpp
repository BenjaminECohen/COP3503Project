#include "Map.h"

Map::Map(std::string mapFile) {

	bool first = true;

}

void Map::Render() {


	std::ifstream input;
	std::string mapString;
	input.open("Assets/Maps/map1.txt");
	std::array<std::string, 12> map;
	int count = 0;

	while (!input.eof()) {
		input >> map[count];
		count++;
	}

	
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 16; j++) {
			if (map[i].at(j) == '1') {
			
				glColor4f(1, 1, 1, 1);
				glBegin(GL_QUADS);
				glTexCoord2f(0, 0);		glVertex2f(j * 64, ((11 - i) * 64));
				glTexCoord2f(1, 0);		glVertex2f(j * 64 + 64, ((11 - i) * 64));
				glTexCoord2f(1, 1);		glVertex2f(j * 64 + 64, ((11 - i) * 64) + 64);
				glTexCoord2f(0, 1);		glVertex2f(j * 64, ((11 - i) * 64) + 64);
				glEnd();
			}
		}
	} 
}

void Map::Update(){

}

void Map::LoadMap(std::string mapFile) {
	
}