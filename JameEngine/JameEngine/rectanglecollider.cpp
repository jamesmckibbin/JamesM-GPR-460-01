#include "rectanglecollider.h"

#include "gameobject.h"

RectangleCollider::RectangleCollider(GameObject* obj)
{
	parentGO = obj;
	colRect.x = 5;
	colRect.y = 5;
	colRect.w = 10;
	colRect.h = 10;
}

RectangleCollider::RectangleCollider(GameObject* obj, float width, float height)
{
	parentGO = obj;
	colRect.x = obj->transform.position.x + width / 2;
	colRect.y = obj->transform.position.y + height / 2;
	colRect.w = width;
	colRect.h = height;
}

void RectangleCollider::Update(float deltaTime)
{
}
