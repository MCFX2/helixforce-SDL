#include "Component.h"

Component::Component(GameObject* parent)
{
	parent_ = parent;
}

GameObject* Component::get_parent()
{
	return parent_;
}
