#pragma once

#include "Component.h"
#include <string>

class Collider;

class CollisionGroup : public Component
{
public:
	CollisionGroup(GameObject* parent);

	void update(float dt) override {};

	void start() override;

	bool does_collide(CollisionGroup*);

	std::string name;
	unsigned id{ 1 };
	//adds a collisiongroup to the list of collisiongroups
	//this will collide with
	void add_collisiongroup(std::string);

	//register a collider to this collisiongroup
	void add_collider(Collider*);
	void remove_collider(Collider*);

	static CollisionGroup* get_collisiongroup(std::string);
private:
	//only used during init
	std::vector<std::string> collides_with_;
	//list of actual collisiongroups this collides with
	std::vector<CollisionGroup*> cwith_list;
	//list of all colliders with this collisiongroup
	std::vector<Collider*> colliders_;
};