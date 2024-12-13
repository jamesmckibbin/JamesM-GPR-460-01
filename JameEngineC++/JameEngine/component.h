#pragma once

#include "utils.h"

class GameObject;

class Component {
public:
	int type;
	virtual void Update(float dt) = 0;
	GameObject* GetOwningGameObject() { return parentGO; }
protected:
	GameObject* parentGO = nullptr;
};