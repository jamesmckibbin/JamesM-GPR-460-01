#pragma once

#include <vector>

#include "scene.h"

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
            Scene::sRectangleRendererPool.Delete(renderer);
        }
        if (collider != nullptr) {
            Scene::sRectangleColliderPool.Delete(collider);
        }
        if (player != nullptr) {
            Scene::sPlayerControllerPool.Delete(player);
        }
        if (colorChanger != nullptr) {
            Scene::sColliderColorChangerPool.Delete(colorChanger);
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

protected:
    RectangleRenderer* renderer = nullptr;
    RectangleCollider* collider = nullptr;
    PlayerController* player = nullptr;
    ColliderColorChanger* colorChanger = nullptr;
};
