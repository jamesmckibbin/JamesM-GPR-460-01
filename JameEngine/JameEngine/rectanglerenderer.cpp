#include "rectanglerenderer.h"

void RectangleRenderer::Update() {
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
