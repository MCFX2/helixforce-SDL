#pragma once

#include "Component.h"
#include "Collider.h"

class BulletBase : public Component
{
public:
	BulletBase(GameObject* parent);

	void start() override;
	void update(float) override {};

	float damage{ 1 };
private:
	void on_collide(const CollisionEvent&);
};