#pragma once

#define SCREENWIDTH 640
#define SCREENHEIGHT 480

#define LEVELS_PATH "levels/"

struct Vector3 {
	float x, y, z;
};

struct Transform {
	Vector3 position;
};
