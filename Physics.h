#pragma once

#include "Component.h"

#include "Vector.h"

class Physics : public Component
{
public:
	Physics(GameObject* parent);

	void update(float dt);

	Vector2 velocity;

private:

};