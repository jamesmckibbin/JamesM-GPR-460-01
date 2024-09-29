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
        renderer = nullptr;
        /*collider = nullptr;
        player = nullptr;
        colorChanger = nullptr;*/
    }

    GameObject(Vector3 pos)
    {
        transform.position = pos;
        renderer = nullptr;
        /*collider = nullptr;
        player = nullptr;
        colorChanger = nullptr;*/
    }

    ~GameObject() {
        delete renderer;
        renderer = nullptr;
    }

    Transform transform;

    RectangleRenderer* GetRenderer() { return renderer; }
    RectangleRenderer* CreateRenderer(float width, float height, Vector3 color);
    /*RectangleCollider* CreateCollider();
    PlayerController* CreatePlayerController();
    ColliderColorChanger* CreateColliderColorChanger();*/

protected:
    RectangleRenderer* renderer;
    /*RectangleCollider* collider;
    PlayerController* player;
    ColliderColorChanger* colorChanger;*/
};
