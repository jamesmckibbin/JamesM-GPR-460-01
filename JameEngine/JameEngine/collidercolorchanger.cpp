#include "collidercolorchanger.h"
#include "gameobject.h"

ColliderColorChanger::ColliderColorChanger()
{
	parentGO = nullptr;
}

ColliderColorChanger::ColliderColorChanger(GameObject* obj)
{
	parentGO = obj;
	color = {100.f, 100.f, 100.f};
	altColor = { 255.f, 255.f, 255.f };
}

ColliderColorChanger::ColliderColorChanger(GameObject* obj, Vector3 color1, Vector3 color2)
{
	parentGO = obj;
	color = color1;
	altColor = color2;
}

void ColliderColorChanger::Update(float dt)
{
	if (parentGO->GetCollider()->isColliding) {
		parentGO->GetRenderer()->color = altColor;
	}
	else {
		parentGO->GetRenderer()->color = color;
	}
}
