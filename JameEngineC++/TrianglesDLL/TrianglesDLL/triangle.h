#pragma once

#ifdef TRIANGLESDLL_EXPORTS
#define TRIANGLES_API __declspec(dllexport)
#else
#define TRIANGLES_API __declspec(dllimport)
#endif

#include "SDL.h"

extern "C" TRIANGLES_API void UpdateTriangleRenderer();

extern "C" TRIANGLES_API void DrawTriangleRenderer(SDL_Renderer * renderTarget, int radius, int centreX, int centreY, Uint8 r, Uint8 g, Uint8 b, Uint8 a);