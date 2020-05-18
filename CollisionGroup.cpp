#include "CollisionGroup.h"
#include "ComponentRegistry.h"
#include "Collider.h"
#include <unordered_map>

REGISTER_COMPONENT("CollisionGroup", CollisionGroup);
//this assigns an id to every collisiongroup, for update optimization purposes
static unsigned current_num_cg = 0;
//this is used to lookup collisiongroups during object init phase
static std::unordered_map<std::string, CollisionGroup*> collision_directory;

//list of collisiongroups so they update in order of id
static std::vector<CollisionGroup*> collision_update_list;

static void SetNameProperty(Component* c, std::istringstream& ss)
{
	CollisionGroup* cg = static_cast<CollisionGroup*>(c);
	ss >> cg->name;
	collision_directory.emplace(cg->name, cg);
}
REGISTER_PROPERTY(CollisionGroup, "Name", SetNameProperty);

static void CollidesWithProperty(Component* c, std::istringstream& ss)
{
	CollisionGroup* cg = static_cast<CollisionGroup*>(c);
	std::string cwith;
	ss >> cwith;
	cg->add_collisiongroup(cwith);
}
REGISTER_PROPERTY(CollisionGroup, "CollidesWith", CollidesWithProperty);

CollisionGroup::CollisionGroup(GameObject* parent) : Component(parent)
	,id(current_num_cg++)
{
	collision_update_list.push_back(this);
}

void CollisionGroup::add_collisiongroup(std::string name_other)
{
	collides_with_.push_back(name_other);
}

void CollisionGroup::add_collider(Collider* c)
{
	colliders_.push_back(c);
}

void CollisionGroup::remove_collider(Collider* c)
{
	auto it = std::find(colliders_.begin(), colliders_.end(), c);
	if (it != colliders_.end())
	{
		colliders_.erase(it);
	}
}

CollisionGroup* CollisionGroup::get_collisiongroup(std::string name)
{
	auto result = collision_directory.find(name);
	if (result == collision_directory.end())
	{
		return nullptr;
	}
	return result->second;
}

//all collisiongroups should be registered by this stage
//now build the actual collision table
void CollisionGroup::start()
{
	for (std::string& cg : collides_with_)
	{
		auto cd = collision_directory.find(cg);
		if (cd == collision_directory.end())
		{
			continue;
		}
		cwith_list.push_back(cd->second);
	}
}

bool CollisionGroup::does_collide(CollisionGroup* cg)
{
	for (CollisionGroup* c : cwith_list)
	{
		if (cg == c) return true;
	}
	return false;
}
