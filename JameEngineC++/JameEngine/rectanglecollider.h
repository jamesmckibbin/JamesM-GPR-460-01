#pragma once

#include "SDL.h"

#include "component.h"

class RectangleCollider : public Component {
public:
	RectangleCollider();
	RectangleCollider(GameObject* obj);
	RectangleCollider(GameObject* obj, float width, float height);

	bool CheckCollision(RectangleCollider* other);

	void Update(float deltaTime) override;

	bool isColliding = false;
private:
	SDL_Rect colRect;
};