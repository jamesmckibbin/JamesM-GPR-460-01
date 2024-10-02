#pragma once

#include "component.h"

class PlayerController : public Component {
public:
	void Update(float dt) override;
private:

	void Update(GameObject* playerobj, float dt);

};
