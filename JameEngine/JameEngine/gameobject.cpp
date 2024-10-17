#include "gameobject.h"

ComponentPool<PlayerController> GameObject::sPlayerControllerPool{ 15 };
ComponentPool<RectangleRenderer> GameObject::sRectangleRendererPool{ 15 };
ComponentPool<RectangleCollider> GameObject::sRectangleColliderPool{ 15 };
ComponentPool<ColliderColorChanger> GameObject::sColliderColorChangerPool{ 15 };

RectangleRenderer* GameObject::CreateRenderer(float width, float height, Vector3 color)
{
    renderer = GameObject::sRectangleRendererPool.New(this, width, height, color);
    return renderer;
}

RectangleCollider* GameObject::CreateCollider(float width, float height)
{
    collider = GameObject::sRectangleColliderPool.New(this, width, height);
    return collider;
}

PlayerController* GameObject::CreatePlayerController(float moveSpeed)
{
    player = GameObject::sPlayerControllerPool.New(this, moveSpeed);
    return player;
}

ColliderColorChanger* GameObject::CreateColliderColorChanger(Vector3 color1, Vector3 color2)
{
    colorChanger = GameObject::sColliderColorChangerPool.New(this, color1, color2);
    return colorChanger;
}

void GameObject::Draw(SDL_Renderer* renderTarget)
{
    if (renderer != nullptr) {
        renderer->Draw(renderTarget, transform.position);
    }
}
