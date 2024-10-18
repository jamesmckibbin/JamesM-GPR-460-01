#pragma once

#include "componentpool.h"
#include "rectanglerenderer.h"
#include "rectanglecollider.h"
#include "playercontroller.h"
#include "collidercolorchanger.h"

class Scene {
public:
    static ComponentPool<PlayerController> sPlayerControllerPool;
    static ComponentPool<RectangleRenderer> sRectangleRendererPool;
    static ComponentPool<RectangleCollider> sRectangleColliderPool;
    static ComponentPool<ColliderColorChanger> sColliderColorChangerPool;
};