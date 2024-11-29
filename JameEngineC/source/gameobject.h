#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "rectanglerenderer.h"
#include "rectanglecollider.h"

typedef struct {
    transform_t transform;
    rectangle_renderer_t* renderer = NULL;
    rectangle_collider_t* collider = NULL;
} game_object_t;

#endif