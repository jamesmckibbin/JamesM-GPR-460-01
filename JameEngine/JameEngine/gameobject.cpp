#include "gameobject.h"

RectangleRenderer* GameObject::CreateRenderer(float width, float height, Vector3 color)
{
    renderer = new RectangleRenderer(width, height, color);
    return renderer;
}
