#pragma once
//player controller behavior class

#include "Vector.h"
#include "Component.h"

class PlayerController : public Component
{
public:
	PlayerController(GameObject* parent);

	void update(float dt);

	float mouseMinDistance_{ 0 };
	float mouseFarDistance_{ 12 };

	float speed_{ 1 };
	Vector2 speedAdjust_{ Vector2(1) };

	Vector2 deceleration_{ Vector2(0) };

	float maxRVelocity_{ 100 };
	float maxLVelocity_{ 100 };
	float maxVVelocity_{ 100 };
private:

	Vector2 ParseMouse();
	void Decelerate();
	void Accelerate();
	void ClampVelocity();
	void ClampPosition();
};