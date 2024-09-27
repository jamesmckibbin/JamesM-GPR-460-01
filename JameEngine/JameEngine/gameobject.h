#pragma once

#include <vector>

#include "transform.h"
#include "rectanglerenderer.h"
#include "rectanglecollider.h"
#include "playercontroller.h"
#include "collidercolorchanger.h"

class GameObject
{

public:
    GameObject()
    {
        // Initialize all components to nullptr
    }

    RectangleRenderer* CreateRenderer(...);
    RectangleCollider* CreateCollider(...);
    PlayerController* CreatePlayerController(...);
    ColliderColorChanger* CreateColliderColorChanger(...);

protected:
    Transform transform;
    RectangleRenderer* renderer;
    RectangleCollider* collider;
    PlayerController* player;
    ColliderColorChanger* colorChanger;
};
