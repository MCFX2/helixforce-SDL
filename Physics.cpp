
#include "Physics.h"
#include "ComponentRegistry.h"

#include "Transform.h"

REGISTER_COMPONENT("Physics", Physics);

Physics::Physics(GameObject* parent) : Component(parent)
{
	parent->get_source().read_properties("Physics", velocity);
}

void Physics::update(float dt)
{
	get_component<Transform>()->translation += (velocity * dt);
}