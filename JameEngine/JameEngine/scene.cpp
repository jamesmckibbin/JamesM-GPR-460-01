#include "scene.h"

std::vector<GameObject*> Scene::sGameObjects{15};
ComponentPool<PlayerController> Scene::sPlayerControllerPool{ 15 };
ComponentPool<RectangleRenderer> Scene::sRectangleRendererPool{ 15 };
ComponentPool<RectangleCollider> Scene::sRectangleColliderPool{ 15 };
ComponentPool<ColliderColorChanger> Scene::sColliderColorChangerPool{ 15 };