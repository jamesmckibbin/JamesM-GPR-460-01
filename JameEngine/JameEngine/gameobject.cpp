#include "gameobject.h"

RectangleRenderer* GameObject::CreateRenderer(float width, float height, Vector3 color)
{
    renderer = new RectangleRenderer(this, width, height, color);
    return renderer;
}

RectangleCollider* GameObject::CreateCollider(float width, float height)
{
    collider = new RectangleCollider(this, width, height);
    return collider;
}

PlayerController* GameObject::CreatePlayerController(float moveSpeed)
{
    player = new PlayerController(this, moveSpeed);
    return player;
}
