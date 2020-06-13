#include "Collider.h"
#include "ComponentRegistry.h"

#include "Transform.h"
#include "CollisionGroup.h"

REGISTER_COMPONENT("Collider", Collider);
REGISTER_SIMPLE_PROPERTY(Collider, "Offset", offset);
REGISTER_SIMPLE_PROPERTY(Collider, "Size", extents);

static std::vector<Collider*> collider_list;

static void CollisionGroupProperty(Component* c, std::istringstream& ss)
{
	std::string colgroup_name;
	ss >> colgroup_name;
	Collider* collider = static_cast<Collider*>(c);
	collider->set_collisiongroup(CollisionGroup::get_collisiongroup(colgroup_name));
}

REGISTER_PROPERTY(Collider, "CollisionGroup", CollisionGroupProperty);

Collider::Collider(GameObject* parent) : Component(parent)
{
	collider_list.push_back(this);
}

Collider::~Collider()
{
	collisionGroup->remove_collider(this);
	for (auto it = collider_list.begin(); it < collider_list.end(); ++it)
	{
		if (*it == this)
		{
			collider_list.erase(it);
			break;
		}
	}
}

void Collider::update_all()
{
	for (auto coll = collider_list.begin(); coll < collider_list.end(); ++coll)
	{
		for (auto other = coll; other < collider_list.end(); ++other)
		{
			Collider* collider = *coll;
			Collider* oCollider = *other;
			if (collider->collisionGroup->does_collide(oCollider->collisionGroup))
			{
				if (collider->is_colliding(oCollider))
				{
					CollisionEvent ce;
					ce.other_group = oCollider->collisionGroup;
					collider->on_collide(ce);
					ce.other_group = collider->collisionGroup;
					oCollider->on_collide(ce);
				}
			}
		}
	}
}

bool Collider::is_colliding(Collider* other)
{
	float rightEdge = transform->translation.x + extents.x;
	float oLeftEdge = other->transform->translation.x - other->extents.x;
	if (rightEdge < oLeftEdge) return false;

	float leftEdge = transform->translation.x - extents.x;
	float oRightEdge = other->transform->translation.x + other->extents.x;
	if (leftEdge > oRightEdge) return false;

	float oBottomEdge = other->transform->translation.y - other->extents.y;
	float topEdge = transform->translation.y + extents.y;
	if (oBottomEdge > topEdge) return false;

	float bottomEdge = transform->translation.y - extents.y;
	float oTopEdge = other->transform->translation.y + other->extents.y;
	if (bottomEdge > oTopEdge) return false;

	return true;
}

void Collider::start()
{
	transform = get_component<Transform>();
}

void Collider::set_collisiongroup(CollisionGroup* cg)
{
	collisionGroup = cg;
	//add collider to cg list
	cg->add_collider(this);
}
