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

ColliderColorChanger* GameObject::CreateColliderColorChanger(Vector3 color1, Vector3 color2)
{
    colorChanger = new ColliderColorChanger(this, color1, color2);
    return colorChanger;
}
