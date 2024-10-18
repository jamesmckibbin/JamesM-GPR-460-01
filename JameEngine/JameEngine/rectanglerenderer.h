#pragma once

#include "SDL.h"

#include "transform.h"
#include "component.h"

class RectangleRenderer : public Component
{
public:
	RectangleRenderer();
	RectangleRenderer(GameObject* obj);
	RectangleRenderer(GameObject* obj, float newwidth, float newheight, Vector3 newcolor);
	void Update(float dt) override;
	void Draw(SDL_Renderer* renderTarget, Vector3 pos);
	float width, height;
	Vector3 color;
	float alpha = 255.f;
};