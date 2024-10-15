#pragma once

#include <vector>

#include "rectanglerenderer.h"
#include "rectanglecollider.h"
#include "playercontroller.h"
#include "collidercolorchanger.h"

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
        delete renderer;
        renderer = nullptr;
        delete player;
        player = nullptr;
        delete collider;
        collider = nullptr;
        delete colorChanger;
        colorChanger = nullptr;
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
