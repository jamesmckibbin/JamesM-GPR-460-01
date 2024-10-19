#include "gameobject.h"

RectangleRenderer* GameObject::CreateRenderer(float width, float height, Vector3 color)
{
    renderer = Scene::sRectangleRendererPool.New(this, width, height, color);
    return renderer;
}

RectangleCollider* GameObject::CreateCollider(float width, float height)
{
    collider = Scene::sRectangleColliderPool.New(this, width, height);
    return collider;
}

PlayerController* GameObject::CreatePlayerController(float moveSpeed)
{
    player = Scene::sPlayerControllerPool.New(this, moveSpeed);
    return player;
}

ColliderColorChanger* GameObject::CreateColliderColorChanger(Vector3 color1, Vector3 color2)
{
    colorChanger = Scene::sColliderColorChangerPool.New(this, color1, color2);
    return colorChanger;
}
