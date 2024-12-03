#pragma once

#include "gameobject.h"
#include <string>
#include <unordered_map>

class Level {
public:
	bool ReadLevelDataFromFile(std::string filename);

	int levelID;
	std::string levelName;
	std::vector<GameObject*> loadedGameObjects;
};
