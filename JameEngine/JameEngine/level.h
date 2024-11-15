#pragma once

#include "gameobject.h"
#include <string>
#include <unordered_map>

class Level {
public:
	void LoadLevelFromFile(std::string filename);

	std::vector<GameObject*> loadedGameObjects;
};
