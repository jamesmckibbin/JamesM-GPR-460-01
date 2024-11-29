#ifndef RECTANGLE_COLLIDER_H
#define RECTANGLE_COLLIDER_H

#include "utils.h"
#include <SDL.h>

struct game_object;
typedef struct game_object game_object_t;

typedef struct {
    game_object_t* parent;
    float width, height;
    bool colliding;
} rectangle_collider_t;

void rectangle_collider_init(rectangle_collider_t* self);
void rectangle_collider_update(rectangle_collider_t* self, float dt);
bool rectangle_collider_check_collision(rectangle_collider_t* self, rectangle_collider_t* other);

#endif