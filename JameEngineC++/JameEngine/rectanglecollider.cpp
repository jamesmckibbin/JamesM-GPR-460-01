#include "rectanglecollider.h"

#include "gameobject.h"

RectangleCollider::RectangleCollider()
{
	parentGO = nullptr;
}

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
	colRect.x = (int)obj->transform.position.x + (int)width / 2;
	colRect.y = (int)obj->transform.position.y + (int)height / 2;
	colRect.w = (int)width;
	colRect.h = (int)height;
}

bool RectangleCollider::CheckCollision(RectangleCollider* other)
{
	SDL_Rect newRect;
	return (SDL_IntersectRect(&colRect, &other->colRect, &newRect));
}

void RectangleCollider::Update(float deltaTime)
{
	colRect.x = (int)parentGO->transform.position.x - colRect.w / 2;
	colRect.y = (int)parentGO->transform.position.y - colRect.h / 2;

	for (int i = 0; i < GameObject::sRectangleColliderPool.GetSize(); i++) {
		if (GameObject::sRectangleColliderPool.GetPoolArrayItemInUse(i) && 
			this != GameObject::sRectangleColliderPool.GetPoolArrayItem(i)) {
			if (CheckCollision(GameObject::sRectangleColliderPool.GetPoolArrayItem(i))) {
				GameObject::sRectangleColliderPool.GetPoolArrayItem(i)->isColliding = true;
				isColliding = true;
				return;
			}
			else {
				GameObject::sRectangleColliderPool.GetPoolArrayItem(i)->isColliding = false;
				isColliding = false;
			}
		}
	}
}
