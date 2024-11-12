#include "level.h"

#include <iostream>
#include <fstream>

void Level::LoadLevelFromFile(std::string filename)
{
	//READ FILE
	std::ifstream levelFile(filename);

	char id;
	float x, y, h, w, r, g, b;
	while (!levelFile.eof())
	{
		levelFile >> id;

		// Game object read
		if (id == '+') {
			levelFile >> x >> y;
			std::cout << "Game object loaded: " << std::endl;
			std::cout << id << " " << x << " " << y << std::endl;
		}
		// Is component
		else {
			switch (id) {
			case '0':
				levelFile >> w >> h >> r >> g >> b;
				std::cout << "RectangleRenderer loaded: " << std::endl;
				std::cout << id << " " << w << " " << h << " " << r << " " << g << " " << b << std::endl;
				break;
			case '1':
				levelFile >> w >> h;
				std::cout << "RectangleCollider loaded: " << std::endl;
				std::cout << id << " " << w << " " << h << std::endl;
				break;

			default:
				break;
			}
		}
	}
	//GRAB GAMEOBJECT AND TRANSFORM
	//WHILE COMPONENTS
	//GRAB COMPONENT

	//CLOSE FILE
	levelFile.close();
}
