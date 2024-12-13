#pragma once

#include "SDL.h"

#include "component.h"

class TriangleRenderer : public Component
{
public:
	TriangleRenderer();
	TriangleRenderer(GameObject* obj);
	TriangleRenderer(GameObject* obj, float newradius, Vector3 newcolor);
	void Update(float dt) override;
	void Draw(SDL_Renderer* renderTarget, Vector3 pos);

	static void LoadTrianglesDLL(bool load);
	static void* triHandle;

	int radius;
	Vector3 color;
	float alpha = 255.f;
};