#pragma once

#include "SDL.h"

#include "component.h"

class RectangleRenderer : public Component
{
public:
	RectangleRenderer() {
		width = 10.f;
		height = 10.f;
		color = { 255.f, 255.f, 255.f };
	}
	RectangleRenderer(float newwidth, float newheight, Vector3 newcolor) {
		width = newwidth;
		height = newheight;
		color = newcolor;
	}
	void Update() override;
	void Draw(SDL_Renderer* renderTarget, Vector3 pos);
	float width, height;
	Vector3 color;
	float alpha = 255.f;
};