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
         for (Component* com : components) {
            if (com->type == 0) {
                GameObject::sRectangleRendererPool.Delete((RectangleRenderer*)com);
            }
            else if (com->type == 1) {
                GameObject::sRectangleColliderPool.Delete((RectangleCollider*)com);
            }
            else if (com->type == 2) {
                GameObject::sPlayerControllerPool.Delete((PlayerController*)com);
            }
            else if (com->type == 3) {
                GameObject::sColliderColorChangerPool.Delete((ColliderColorChanger*)com);
            }
            else if (com->type == 4) {
                GameObject::sTriangleRendererPool.Delete((TriangleRenderer*)com);
            }
        }
    }

    Transform transform;

    RectangleRenderer* GetRectangleRenderer();
    RectangleCollider* GetCollider();
    PlayerController* GetPlayerController();
    ColliderColorChanger* GetColliderColorChanger();
    TriangleRenderer* GetTriangleRenderer();

    RectangleRenderer* CreateRectangleRenderer(float width, float height, Vector3 color);
    RectangleCollider* CreateCollider(float width, float height);
    PlayerController* CreatePlayerController(float moveSpeed);
    ColliderColorChanger* CreateColliderColorChanger(Vector3 color1, Vector3 color2);
    TriangleRenderer* CreateTriangleRenderer(float radius, Vector3 color);

    static ComponentPool<PlayerController> sPlayerControllerPool;
    static ComponentPool<RectangleRenderer> sRectangleRendererPool;
    static ComponentPool<RectangleCollider> sRectangleColliderPool;
    static ComponentPool<ColliderColorChanger> sColliderColorChangerPool;
    static ComponentPool<TriangleRenderer> sTriangleRendererPool;

protected:
    std::vector<Component*> components;
};
