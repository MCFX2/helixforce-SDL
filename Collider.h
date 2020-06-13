#pragma once

#include "Component.h"
#include "Vector.h"
#include "Delegate.h"

class CollisionGroup;
class Transform;

struct CollisionEvent
{
	CollisionGroup* other_group;

};

class Collider : public Component
{
public:
	Collider(GameObject* parent);
	~Collider();

	void update(float dt) override {};

	void start() override;

	virtual bool is_colliding(Collider* other);

	void set_collisiongroup(CollisionGroup*);
	//CollisionGroup* get_collisionGroup() { return collisionGroup; };

	static void update_all();

	Vector2 offset{ Vector2() };
	Vector2 extents{ Vector2() };

	Delegate<const CollisionEvent&> on_collide;

private:

	CollisionGroup* collisionGroup{ nullptr };
	Transform* transform{ nullptr };
};