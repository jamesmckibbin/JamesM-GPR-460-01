#ifndef UTILS_H
#define UTILS_H

#define SCREENWIDTH 640
#define SCREENHEIGHT 480

#include <stdbool.h>

typedef struct {
    float r, g, b, a;
} color_t;

typedef struct {
    float x, y, z;
} vec3_t;

typedef struct {
    vec3_t position;
} transform_t;

#endif