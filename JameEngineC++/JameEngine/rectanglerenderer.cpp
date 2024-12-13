#include "rectanglerenderer.h"

RectangleRenderer::RectangleRenderer()
{
	type = 0;
	parentGO = nullptr;
}

RectangleRenderer::RectangleRenderer(GameObject* obj)
{
	type = 0;
	parentGO = obj;
	width = 10.f;
	height = 10.f;
	color = { 255.f, 255.f, 255.f };
}

RectangleRenderer::RectangleRenderer(GameObject* obj, float newwidth, float newheight, Vector3 newcolor)
{
	type = 0;
	parentGO = obj;
	width = newwidth;
	height = newheight;
	color = newcolor;
}

void RectangleRenderer::Update(float dt) {
	// do nothing
}

void RectangleRenderer::Draw(SDL_Renderer* renderTarget, Vector3 pos)
{
	SDL_Rect newRect;
	newRect.x = (int)(pos.x - (width / 2));
	newRect.y = (int)(pos.y - (height / 2));
	newRect.w = (int)width;
	newRect.h = (int)height;
	SDL_SetRenderDrawColor(renderTarget, (Uint8)color.x, (Uint8)color.y, (Uint8)color.z, (Uint8)alpha);
	SDL_RenderFillRect(renderTarget, &newRect);
	SDL_SetRenderDrawColor(renderTarget, 0, 0, 0, 255);
}
