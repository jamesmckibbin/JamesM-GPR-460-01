#ifndef RECTANGLE_RENDERER_H
#define RECTANGLE_RENDERER_H

#include "utils.h"
#include <SDL.h>

struct game_object;
typedef struct game_object game_object_t;

typedef struct {
    game_object_t* parent;
    float width, height;
    color_t color;
} rectangle_renderer_t;

void rectangle_renderer_init(rectangle_renderer_t* self);
void rectangle_renderer_update(rectangle_renderer_t* self, float dt);
void rectangle_renderer_draw(rectangle_renderer_t* self, SDL_Renderer* renderer);

#endif