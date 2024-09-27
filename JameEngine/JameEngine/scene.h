#pragma once

#include <string>

#include "gameobject.h"

class Scene
{
	Scene(std::string sceneName) {
		name = sceneName;
	}
	~Scene() {
		goPool->clear();
		delete goPool;
		goPool = nullptr;
	}
public:

	// getters

private:
	std::string name;
	std::vector<GameObject>* goPool = new std::vector<GameObject>();
};

