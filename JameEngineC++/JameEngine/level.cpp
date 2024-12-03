#include "level.h"

#include <iostream>
#include <fstream>

void Level::LoadLevelFromFile(std::string filename)
{
	std::ifstream levelFile(filename);

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
			levelFile >> id;
			levelID = id;
		}
		// Level name read
		else if (id == '=') {
			std::getline(levelFile, levelName);
			std::cout << levelName << std::endl;
		}
		// Game object read
		else if (id == '+') {
			if (newGO != nullptr) {
				loadedGameObjects.push_back(newGO);
			}

			levelFile >> x >> y;
			std::cout << "Game object loaded: " << std::endl;
			std::cout << id << " " << x << " " << y << std::endl;
			newGO = new GameObject(Vector3{ x, y, 0 });
		}
		// Is component
		else {
			switch (id) {
			case '0':
				levelFile >> w >> h >> r >> g >> b;
				std::cout << "RectangleRenderer loaded" << std::endl;
				newGO->CreateRenderer(w, h, Vector3{r, g, b});
				break;
			case '1':
				levelFile >> w >> h;
				std::cout << "RectangleCollider loaded" << std::endl;
				newGO->CreateCollider(w, h);
				break;
			case '2':
				levelFile >> s;
				std::cout << "PlayerController loaded" << std::endl;
				newGO->CreatePlayerController(s);
				break; 
			case '3':
				levelFile >> r >> g >> b >> r2 >> g2 >> b2;
				std::cout << "ColliderColorChanger loaded" << std::endl;
				newGO->CreateColliderColorChanger(Vector3{r, g, b}, Vector3{r2, g2, b2});
				break;

			default:
				break;
			}
		}
	}

	levelFile.close();
}
