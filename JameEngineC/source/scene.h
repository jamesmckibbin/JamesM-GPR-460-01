#ifndef SCENE_H
#define SCENE_H

#include "gameobject.h"

typedef struct {
    game_object_t* active_game_objects;
    game_object_t* background = NULL;
    game_object_t* player = NULL;
    Uint32 last_frame_time, delta_time = 1;
    bool debug_key = false;
    bool print_fps = false;
    bool chaos = false;
} scene_t;



#endif