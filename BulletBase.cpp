#include "BulletBase.h"
#include "CollisionGroup.h"
#include "ComponentRegistry.h"

REGISTER_COMPONENT("BulletBase", BulletBase);
REGISTER_SIMPLE_PROPERTY(BulletBase, "Damage", damage);

BulletBase::BulletBase(GameObject* parent) : Component(parent)
{

}

void BulletBase::start()
{
	hndl_collide_ = get_component<Collider>()->on_collide.subscribe(this, &BulletBase::on_collide);
}

void BulletBase::on_collide(const CollisionEvent& ce)
{
	if (ce.other_group->name == "PlayerEnemy")
	{
		get_parent()->destroy();
	}
}
