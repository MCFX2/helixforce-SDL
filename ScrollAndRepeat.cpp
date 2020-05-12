#include "ScrollAndRepeat.h"

#include "ComponentRegistry.h"
#include "MathUtils.h"
#include "Transform.h"

REGISTER_COMPONENT("ScrollAndRepeat", ScrollAndRepeat);
REGISTER_SIMPLE_PROPERTY(ScrollAndRepeat, "Speed", speed);

void ScrollAndRepeat::start()
{
	transform = get_component<Transform>();
}

void ScrollAndRepeat::update(float dt)
{
	transform->translation.x += dt * speed;
	curOffset_ += Util::Abs(dt * speed);
	if (curOffset_ > transform->scale.x)
	{
		transform->translation.x -= transform->scale.x * (speed > 0 ? 1 : -1);
		curOffset_ -= transform->scale.x;
	}
}

ScrollAndRepeat::ScrollAndRepeat(GameObject* parent) : Component(parent) { }
