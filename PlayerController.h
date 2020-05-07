#pragma once
//player controller behavior class

#include "Vector.h"
#include "Component.h"

#include <functional>

class PlayerController : public Component
{
public:
	PlayerController(GameObject* parent);

	void update(float dt);

private:

	Vector2 ParseMouse();

	float mouseMinDistance_;
	float mouseFarDistance_;

	float speed_;
	Vector2 speedAdjust_;

	Vector2 deceleration_;
};