#pragma once

#include "component.h"

class ColliderColorChanger : public Component {
public:
	ColliderColorChanger();
	ColliderColorChanger(GameObject* obj);
	ColliderColorChanger(GameObject* obj, Vector3 color1, Vector3 color2);
	void Update(float dt) override;
protected:
	Vector3 color = {0, 0, 0};
	Vector3 altColor = { 0, 0, 0 };;
};
