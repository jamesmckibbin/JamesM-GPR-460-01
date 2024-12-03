#pragma once

#include "gameobject.h"
#include <string>
#include <unordered_map>

class Level {
public:
	void ReadLevelNameAndID(std::string filename);
	void LoadLevelFromFile(std::string filename);

	int levelID;
	std::string levelName;
	std::vector<GameObject*> loadedGameObjects;
};
