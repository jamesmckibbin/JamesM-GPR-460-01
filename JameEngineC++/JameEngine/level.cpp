#include "level.h"

#include <iostream>
#include <fstream>

bool Level::ReadLevelDataFromFile(std::string filename)
{
	std::ifstream levelFile(filename);

	if (levelFile.fail()) {
		std::cout << "File failed to open" << std::endl;
		return false;
	}

	GameObject* newGO = nullptr;

	std::string commentBuffer;
	char id;
	float x, y, h, w, s, r, g, b, r2, g2, b2;
	while (!levelFile.eof())
	{
		levelFile >> id;
		// Is comment
		if (id == '*') {
			std::getline(levelFile, commentBuffer);
		}
		// Level ID read
		else if (id == '-') {
			levelFile >> levelID;
		}
		// Level name read
		else if (id == '=') {
			std::getline(levelFile, levelName);
		}
		// Game object read
		else if (id == '+') {
			if (newGO != nullptr) {
				loadedGameObjects.push_back(newGO);
			}

			levelFile >> x >> y;
			newGO = new GameObject(Vector3{ x, y, 0 });
		}
		// Is component
		else {
			switch (id) {
			case '0':
				levelFile >> w >> h >> r >> g >> b;
				newGO->CreateRenderer(w, h, Vector3{r, g, b});
				break;
			case '1':
				levelFile >> w >> h;
				newGO->CreateCollider(w, h);
				break;
			case '2':
				levelFile >> s;
				newGO->CreatePlayerController(s);
				break; 
			case '3':
				levelFile >> r >> g >> b >> r2 >> g2 >> b2;
				newGO->CreateColliderColorChanger(Vector3{r, g, b}, Vector3{r2, g2, b2});
				break;

			default:
				break;
			}
		}
	}
	levelFile.close();

	return true;
}
