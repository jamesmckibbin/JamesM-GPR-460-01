#pragma once

#include "SDL.h"

#include "component.h"

class RectangleCollider : public Component {
public:
	RectangleCollider(GameObject* obj);
	RectangleCollider(GameObject* obj, float width, float height);

	void Update(float deltaTime) override;
private:
	SDL_Rect colRect;
};