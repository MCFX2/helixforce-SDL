
#include "Physics.h"
#include "ComponentRegistry.h"

#include "Transform.h"

REGISTER_COMPONENT("Physics", Physics);
REGISTER_SIMPLE_PROPERTY(Physics, "InitialVelocity", velocity);

Physics::Physics(GameObject* parent) : Component(parent)
{
}

void Physics::update(float dt)
{
	get_component<Transform>()->translation += (velocity * dt);
}