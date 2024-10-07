#pragma once

#include "transform.h"
#include "component.h"

class ColliderColorChanger : public Component {
public:
	ColliderColorChanger(GameObject* obj);
	ColliderColorChanger(GameObject* obj, Vector3 color1, Vector3 color2);
	void Update(float dt) override;
protected:
	Vector3 color;
	Vector3 altColor;
};
