#pragma once

#include "component.h"

class PlayerController : public Component {
public:
	PlayerController();
	PlayerController(GameObject* obj, float moveSpeed);
	void Update(float dt) override;
private:
	float speed = 10.f;
};
