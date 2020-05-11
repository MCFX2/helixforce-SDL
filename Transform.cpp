
#include "Transform.h"
#include "ComponentRegistry.h"
#include "GameObject.h"

REGISTER_COMPONENT("Transform", Transform);
REGISTER_SIMPLE_PROPERTY(Transform, "Translation", translation);
REGISTER_SIMPLE_PROPERTY(Transform, "Scale", scale);
REGISTER_SIMPLE_PROPERTY(Transform, "Rotation", rotation);

Transform::Transform(GameObject* parent) : Component(parent)
{
}