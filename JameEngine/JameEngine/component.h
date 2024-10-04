#pragma once

class GameObject;

class Component {
public:
	Component() = default;

	virtual void Update(float dt) = 0;

protected:
	GameObject* parentGO = nullptr;
};