#pragma once
#pragma once
//player controller behavior class


#include "Vector.h"
#include "Component.h"

class Transform;

class ScrollAndRepeat : public Component
{
public:
	ScrollAndRepeat(GameObject* parent);

	void start() override;
	void update(float dt) override;

	float speed{ 1 };
private:
	float curOffset_{ 0 };
	Transform* transform{ nullptr };
};