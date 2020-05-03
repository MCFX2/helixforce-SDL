#pragma once
//player controller behavior class

#include "Vector.h"
#include "Component.h"

class PlayerController : public Component
{
	PlayerController();

	void update();

private:

	Vector2 ParseMouse();

	float mouseMinDistance_;
	float mouseFarDistance_;

	float speed_;
	Vector2 speedAdjust_;

	Vector2 deceleration_;
};