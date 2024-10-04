#pragma once

#include "component.h"

class PlayerController : public Component {
public:
	PlayerController(GameObject* obj, float moveSpeed);
	void Update(float dt) override;
private:
	float speed;
};
