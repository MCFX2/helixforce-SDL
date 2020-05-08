
#include "Transform.h"
#include "ComponentRegistry.h"
#include "GameObject.h"

REGISTER_COMPONENT("Transform", Transform);

Transform::Transform(GameObject* parent) : Component(parent)
{
	parent->get_source().read_properties("Transform", translation, scale, rotation);
}