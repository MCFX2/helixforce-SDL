#pragma once

#include "Component.h"
#include "Vector.h"
#include <functional>

class CollisionGroup;
class Transform;

class Collider : public Component
{
public:
	Collider(GameObject* parent);
	~Collider();

	using CollisionHandler = std::function<void(void*, GameObject*)>;

	void update(float dt) override {};

	void start() override;

	virtual bool is_colliding(Collider* other);

	void set_collisiongroup(CollisionGroup*);
	CollisionGroup* get_collisionGroup() { return collisionGroup; };

	void register_collision_handler(CollisionHandler);
	void unregister_collision_handler(CollisionHandler);

	Vector2 offset{ Vector2() };
	Vector2 extents{ Vector2() };
private:
	std::vector<CollisionHandler> collision_handlers;
	CollisionGroup* collisionGroup{ nullptr };
	Transform* transform{ nullptr };
};