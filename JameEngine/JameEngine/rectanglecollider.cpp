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

bool RectangleCollider::CheckCollision(RectangleCollider* other)
{
	SDL_Rect newRect;
	return (SDL_IntersectRect(&colRect, &other->colRect, &newRect));
}

void RectangleCollider::Update(float deltaTime)
{
	colRect.x = parentGO->transform.position.x - colRect.w / 2;
	colRect.y = parentGO->transform.position.y + colRect.h / 2;
}
