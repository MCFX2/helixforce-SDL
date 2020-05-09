#pragma once

#include "Component.h"

#include "Vector.h"

class Transform : public Component
{
public:
	Transform(GameObject* parent);

	void update(float dt) {};

	Vector2 translation{ Vector2(0) };
	Vector2 scale{ Vector2(100) };
	float rotation{ 0 };

private:

};