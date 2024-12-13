#include "pch.h"
#include <utility>
#include "triangle.h"
#include "SDL.h"

void TRIANGLES_API UpdateTriangleRenderer()
{
	// does nothing, same as rectangle
}

void TRIANGLES_API DrawTriangleRenderer(SDL_Renderer* renderTarget, int radius, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Point points[4];
	points[0].x = x; points[0].y = y - radius;
	points[1].x = x - radius; points[1].y = y + radius;
	points[2].x = x + radius; points[2].y = y + radius;
	points[3].x = x; points[3].y = y - radius;
	SDL_RenderDrawLines(renderTarget, points, 4);
}