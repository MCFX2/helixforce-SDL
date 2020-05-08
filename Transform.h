#pragma once

#include "Component.h"

#include "Vector.h"

class Transform : public Component
{
public:
	Transform(GameObject* parent);

	void update(float dt) {};

	Vector2 translation;
	Vector2 scale;
	float rotation;

private:

};