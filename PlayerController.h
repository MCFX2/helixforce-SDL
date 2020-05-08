#pragma once
//player controller behavior class

#include "Vector.h"
#include "Component.h"

class PlayerController : public Component
{
public:
	PlayerController(GameObject* parent);

	void update(float dt);

private:

	Vector2 ParseMouse();
	void Decelerate();
	void Accelerate();
	void ClampVelocity();
	void ClampPosition();

	float mouseMinDistance_;
	float mouseFarDistance_;

	float speed_;
	Vector2 speedAdjust_;

	Vector2 deceleration_;

	float maxRVelocity_;
	float maxLVelocity_;
	float maxVVelocity_;
};