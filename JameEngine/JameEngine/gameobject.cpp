#include "gameobject.h"

RectangleRenderer* GameObject::CreateRenderer(float width, float height, Vector3 color)
{
    return new RectangleRenderer(width, height, color);
}

PlayerController* GameObject::CreatePlayerController()
{
    return new PlayerController();
}
