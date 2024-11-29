#pragma once

#include <vector>

#include "componentpool.h"

class GameObject
{

public:
    GameObject()
    {
        transform.position = {0.f, 0.f, 0.f};
    }

    GameObject(Vector3 pos)
    {
        transform.position = pos;
    }

    ~GameObject() {
        if (renderer != nullptr) {
            GameObject::sRectangleRendererPool.Delete(renderer);
        }
        if (collider != nullptr) {
            GameObject::sRectangleColliderPool.Delete(collider);
        }
        if (player != nullptr) {
            GameObject::sPlayerControllerPool.Delete(player);
        }
        if (colorChanger != nullptr) {
            GameObject::sColliderColorChangerPool.Delete(colorChanger);
        }
    }

    Transform transform;

    RectangleRenderer* GetRenderer() { return renderer; }
    RectangleRenderer* CreateRenderer(float width, float height, Vector3 color);
    RectangleCollider* GetCollider() { return collider; }
    RectangleCollider* CreateCollider(float width, float height);
    PlayerController* GetPlayerController() { return player; }
    PlayerController* CreatePlayerController(float moveSpeed);
    ColliderColorChanger* GetColliderColorChanger() { return colorChanger; }
    ColliderColorChanger* CreateColliderColorChanger(Vector3 color1, Vector3 color2);

    static ComponentPool<PlayerController> sPlayerControllerPool;
    static ComponentPool<RectangleRenderer> sRectangleRendererPool;
    static ComponentPool<RectangleCollider> sRectangleColliderPool;
    static ComponentPool<ColliderColorChanger> sColliderColorChangerPool;

protected:
    RectangleRenderer* renderer = nullptr;
    RectangleCollider* collider = nullptr;
    PlayerController* player = nullptr;
    ColliderColorChanger* colorChanger = nullptr;
};
