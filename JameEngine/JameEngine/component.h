#pragma once

#include "transform.h"

class Component {
public:
	virtual void Update(float dt) = 0;
};