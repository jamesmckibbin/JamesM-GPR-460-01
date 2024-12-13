#include "trianglerenderer.h"
#include <iostream>

typedef void (*updTri)();
typedef void (*drawTri)(SDL_Renderer*, int, int, int, Uint8, Uint8, Uint8, Uint8);
void* TriangleRenderer::triHandle = nullptr;

TriangleRenderer::TriangleRenderer()
{
	type = 4;
	parentGO = nullptr;
}

TriangleRenderer::TriangleRenderer(GameObject* obj)
{
	type = 4;
	parentGO = obj;
	radius = 10;
	color = { 255.f, 255.f, 255.f };
}

TriangleRenderer::TriangleRenderer(GameObject* obj, float newradius, Vector3 newcolor)
{
	type = 4;
	parentGO = obj;
	radius = newradius;
	color = newcolor;
}

void TriangleRenderer::Update(float dt)
{
	updTri ufx = (updTri)SDL_LoadFunction(TriangleRenderer::triHandle, "UpdateTriangleRenderer");
	ufx();
}

void TriangleRenderer::Draw(SDL_Renderer* renderTarget, Vector3 pos)
{
	SDL_SetRenderDrawColor(renderTarget, (Uint8)color.x, (Uint8)color.y, (Uint8)color.z, (Uint8)alpha);
	if (TriangleRenderer::triHandle) {
		drawTri tfx = (drawTri)SDL_LoadFunction(TriangleRenderer::triHandle, "DrawTriangleRenderer");
		tfx(renderTarget, radius, pos.x, pos.y, color.x, color.y, color.z, alpha);
	}
	SDL_SetRenderDrawColor(renderTarget, 0, 0, 0, 255);
}

void TriangleRenderer::LoadTrianglesDLL(bool load) {
	if (load) {
		TriangleRenderer::triHandle = SDL_LoadObject("TrianglesDLL.dll");
	}
	else {
		SDL_UnloadObject(TriangleRenderer::triHandle);
	}
}
