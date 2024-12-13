#include "gameobject.h"

ComponentPool<PlayerController> GameObject::sPlayerControllerPool{ 15 };
ComponentPool<RectangleRenderer> GameObject::sRectangleRendererPool{ 15 };
ComponentPool<RectangleCollider> GameObject::sRectangleColliderPool{ 15 };
ComponentPool<ColliderColorChanger> GameObject::sColliderColorChangerPool{ 15 };
ComponentPool<TriangleRenderer> GameObject::sTriangleRendererPool{ 15 };

RectangleRenderer* GameObject::GetRectangleRenderer()
{
    for (Component* com : components) {
        if (com->type == 0) {
            return (RectangleRenderer*)com;
        }
    }
}

RectangleRenderer* GameObject::CreateRectangleRenderer(float width, float height, Vector3 color)
{
    RectangleRenderer* rectangle = GameObject::sRectangleRendererPool.New(this, width, height, color);
    components.push_back(rectangle);
    return rectangle;
}

RectangleCollider* GameObject::GetCollider()
{
    for (Component* com : components) {
        if (com->type == 1) {
            return (RectangleCollider*)com;
        }
    }
}

RectangleCollider* GameObject::CreateCollider(float width, float height)
{
    RectangleCollider* collider = GameObject::sRectangleColliderPool.New(this, width, height);
    components.push_back(collider);
    return collider;
}

PlayerController* GameObject::GetPlayerController()
{
    for (Component* com : components) {
        if (com->type == 2) {
            return (PlayerController*)com;
        }
    }
}

PlayerController* GameObject::CreatePlayerController(float moveSpeed)
{
    PlayerController* player = GameObject::sPlayerControllerPool.New(this, moveSpeed);
    components.push_back(player);
    return player;
}

ColliderColorChanger* GameObject::GetColliderColorChanger()
{
    for (Component* com : components) {
        if (com->type == 3) {
            return (ColliderColorChanger*)com;
        }
    }
}

TriangleRenderer* GameObject::GetTriangleRenderer()
{
    for (Component* com : components) {
        if (com->type == 4) {
            return (TriangleRenderer*)com;
        }
    }
}

ColliderColorChanger* GameObject::CreateColliderColorChanger(Vector3 color1, Vector3 color2)
{
    ColliderColorChanger* colorChanger = GameObject::sColliderColorChangerPool.New(this, color1, color2);
    components.push_back(colorChanger);
    return colorChanger;
}

TriangleRenderer* GameObject::CreateTriangleRenderer(float radius, Vector3 color)
{
    TriangleRenderer* circle = GameObject::sTriangleRendererPool.New(this, radius, color);
    components.push_back(circle);
    return circle;
}
